#include <string>
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h> 
#include <moveit_msgs/DisplayRobotState.h> 
#include <moveit_msgs/DisplayTrajectory.h> 
#include <moveit_msgs/AttachedCollisionObject.h> 
#include <moveit_msgs/CollisionObject.h> 
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float64.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <robotiq_2f_gripper_control/Robotiq2FGripper_robot_output.h>

bool flag =  0; //是否接收到相机开启的信号
Eigen::MatrixXd PosLen;    //用来存储接收到的物块位姿信息
Eigen::MatrixXd Point3D;
int result;

void PosLenCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
    int len;
    std::vector<double> pos_len = msg->data;
    ROS_INFO("I heard Position and Length!");
    len = msg->data.size();
    PosLen = Eigen::Map<Eigen::MatrixXd> (pos_len.data(), len / 3, 3);
}

void ResultCallback(const std_msgs::Float64::ConstPtr& msg)
{
    ROS_INFO("I heard Result : %f!", msg->data);
    flag = 1;
    result = msg->data;
}

void PointCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
    int len;
    std::vector<double> pt_3D = msg->data;
    ROS_INFO("I heard Result Point3D!");
    len = msg->data.size();
    Point3D = Eigen::Map<Eigen::MatrixXd> (pt_3D.data(), len / 3, 3);
}

//旋转矢量到四元数
Eigen::Quaterniond rotationVector_quaternion(Eigen::Matrix<double,3,1> rotationVector)
{
    Eigen::Quaterniond quaternion;
    double theat = rotationVector.norm();
    quaternion.w() = cos(theat / 2);
    if(abs(theat) < 0.0001){
    theat += theat > 0 ? 0.0001 : -0.0001;
    }
    quaternion.x() = rotationVector[0] / theat * sin(theat / 2);
    quaternion.y() = rotationVector[1] / theat * sin(theat / 2);
    quaternion.z() = rotationVector[2] / theat * sin(theat / 2);
    return quaternion;
}

//旋转矩阵转换为欧拉ZYX/RPY
//ZYX顺序，即先绕x轴roll,再绕y轴pitch,最后绕z轴yaw,0表示X轴,1表示Y轴,2表示Z轴
Eigen::Vector3d  rotationMatrix_RPY(Eigen::Matrix3d rotationMatrix){
    return rotationMatrix.eulerAngles(2, 1, 0);
}

int main(int argc, char **argv)
{
    //初始化节点
	ros::init(argc, argv, "bci_ur5");
    ros::NodeHandle nh; 
    //引入多线程
	ros::AsyncSpinner spinner(1);
    //开启多线程
	spinner.start();
    //定义订阅器，用来接收相机发布的信息,与脑电分析节点发布的结果信息
    //PositionLength_Pub = nh.advertise<std_msgs::Float64MultiArray>("PositionLengthNode", 10);
    ros::Subscriber PositionLength_Sub = nh.subscribe("/PositionLengthNode", 10, &PosLenCallback);
    ros::Subscriber Result_Sub = nh.subscribe("/result", 10, &ResultCallback);
    ros::Subscriber Point_Sub = nh.subscribe("/Point3D", 1, &PointCallback);
    ros::Rate loop_rate(10);

    //初始化夹爪相关数据类型
    ros::Publisher grip_Pub = nh.advertise<robotiq_2f_gripper_control::Robotiq2FGripper_robot_output>("/Robotiq2FGripperRobotOutput", 10);
    robotiq_2f_gripper_control::Robotiq2FGripper_robot_output GripperOutput;
    GripperOutput.rACT = 1;
    GripperOutput.rGTO = 1;
    GripperOutput.rATR = 0;
    GripperOutput.rPR = 0;      //0时打开，255时完全闭合
    GripperOutput.rSP = 255;
    GripperOutput.rFR = 150;
    grip_Pub.publish(GripperOutput);

    //五个物块序号对应的闪烁频率
    double fre[5] = {8, 10, 12, 14, 16};

    //初始化需要使用 move_group 控制的机械臂中的 arm_group
    //对应moveit中选择的规划部分
    moveit::planning_interface::MoveGroupInterface arm_group("manipulator");

    //获取终端 link 的名称
    //************这里试着用tf新建一个末端坐标系，以夹爪中心为坐标原点*****************
    std::string end_effector_link = arm_group.getEndEffectorLink();
    //设置目标位置所使用的参考坐标系
    std::string reference_frame = "base_link";
    arm_group.setPoseReferenceFrame(reference_frame);
    //设置机械臂运动的允许误差
    arm_group.setGoalJointTolerance(0.001);
    //设置位置（单位：米）和姿态（单位：弧度）的允许误差
    arm_group.setGoalPositionTolerance(0.001);
    arm_group.setGoalOrientationTolerance(0.001);
    //设置允许的最大加速度和速度
    arm_group.setMaxAccelerationScalingFactor(0.2);
    arm_group.setMaxVelocityScalingFactor(0.2);
    //当运动规划失败后，允许重新规划
    arm_group.allowReplanning(true);

    std::vector<std::string> default_set = arm_group.getNamedTargets();
    ROS_INFO("已有的目标名称：%s,  %s", default_set[0],default_set[1]);
    //控制机械臂先回到"up"的位置状态
    arm_group.setStartStateToCurrentState();
    arm_group.setNamedTarget("up");
    ROS_INFO("Let's go up!");
    arm_group.move(); //规划＋运动
    sleep(3);

    //获取当前位姿数据“x、y、z + 四元数”，作为机械臂运动的起始位姿
    geometry_msgs::PoseStamped cur_start_pose = arm_group.getCurrentPose(end_effector_link);
    //ROS_INFO(cur_start_pose.header);
    //初始化路径点向量列表
    std::vector<geometry_msgs::Pose> waypoints;
    //将初始位姿加入路径点向量列表
    waypoints.push_back(cur_start_pose.pose);
    /**************这一步，先运动到物块上方****************/
    //定义一个数组，存放位姿信息
    double INITPose[7] = {0.391410, -0.676384, -0.376217,
                                0.0, 1.052834, 0.454125};
    cur_start_pose.pose.position.x = INITPose[0];
    cur_start_pose.pose.position.y = INITPose[1];
    cur_start_pose.pose.position.z = INITPose[2];
    cur_start_pose.pose.orientation.w = INITPose[3];
    cur_start_pose.pose.orientation.x = INITPose[4];
    cur_start_pose.pose.orientation.y = INITPose[5];
    cur_start_pose.pose.orientation.z = INITPose[7];
    //将目标位姿写入,同时重新设置最大加速度与最大速度
    arm_group.setPoseTarget(cur_start_pose);
    arm_group.setMaxAccelerationScalingFactor(0.2);
    arm_group.setMaxVelocityScalingFactor(0.2);
    //进行运动规划，计算机器人移动到目标的运动轨迹,此时只计算出轨迹，并不会控制机械臂运动
    //对应moveit中的plan按钮，这里提前定义一个初始化的plan按钮，在循环中新建的按钮都由该plan_move赋值
    moveit::planning_interface::MoveGroupInterface::Plan plan_move_init, plan_move_use;
    bool success_plan;
    success_plan = arm_group.plan(plan_move_use) == moveit::planning_interface::MoveItErrorCode::SUCCESS;;
    // moveit::planning_interface::MoveItErrorCode plan_move_use = arm_group.plan(plan_move_use);
    ROS_INFO("Visualizing plan 1 (pose goal) %s",success_plan?"":"FAILED"); 
    //让机械臂按照规划的轨迹开始运动
    //对应moveit中的execute按钮
    if(success_plan)
        arm_group.execute(plan_move_use);
    sleep(1);
    
    while(ros::ok())
    {
        //当获取到相机发布的位姿信息后，只需要将信息存储，当接收到分析结果时，开始进行轨迹规划并运动
        if(flag)
        {
            //获取当前位姿，并将其作为第一个轨迹点，如果报错，则将这里删去，错误原因有可能是不能将当前点放入waypoints中
            geometry_msgs::PoseStamped cur_pose;
            cur_pose = arm_group.getCurrentPose(end_effector_link);
            waypoints.push_back(cur_pose.pose);
            int i;
            //结果是第i个物块
            for (i = 0 ; i < 5 ; i++)
            {
                if(result == fre[i])
                    break;
            }
            //目标抓取姿态为绕x轴旋转180度
            Eigen::Matrix3d gripPose;
            Eigen::Matrix<double,3,1> rotVec;
            Eigen::Quaterniond targetQ;
            gripPose << 1, 0, 0,
                                    0, -1, 0,
                                    0, 0, -1;
            cur_pose.pose.position.x = Point3D(i, 0);
            cur_pose.pose.position.y = Point3D(i, 1);
            //抓取时，由于要考虑夹爪位置，需要将机械臂末端移动到目标点上方一定距离处以方便抓取
            cur_pose.pose.position.z = Point3D(i, 2) + 0.5;
            rotVec = Eigen::Map<Eigen::Matrix<double, 3, 1>> (rotationMatrix_RPY(gripPose).data());
            targetQ = rotationVector_quaternion(rotVec);
            cur_pose.pose.orientation.w = targetQ.w();
            cur_pose.pose.orientation.x = targetQ.x();
            cur_pose.pose.orientation.y = targetQ.y();
            cur_pose.pose.orientation.z = targetQ.z();
            waypoints.push_back(cur_pose.pose); 
            ROS_INFO("轨迹点设置完毕！");
            //将目标位姿写入,同时重新设置最大加速度与最大速度
            arm_group.setPoseTarget(cur_pose);
            arm_group.setMaxAccelerationScalingFactor(0.2);
            arm_group.setMaxVelocityScalingFactor(0.2);
            //进行运动规划，计算机器人移动到目标的运动轨迹,此时只计算出轨迹，并不会控制机械臂运动
            //对应moveit中的plan按钮
            plan_move_use = plan_move_init;
            success_plan = arm_group.plan(plan_move_use) == moveit::planning_interface::MoveItErrorCode::SUCCESS;;
            // moveit::planning_interface::MoveItErrorCode success_plan = arm_group.plan(plan_move_use);
            ROS_INFO("Visualizing plan 2 (pose goal) %s",success_plan?"":"FAILED"); 
            //让机械臂按照规划的轨迹开始运动
            //对应moveit中的execute按钮
            if(success_plan)
                arm_group.execute(plan_move_use);
            sleep(1);
            
            //关闭夹爪
            GripperOutput.rPR = 200;
            grip_Pub.publish(GripperOutput);
            sleep(1);
            //回到初始点处
            //将目标位姿写入,同时重新设置最大加速度与最大速度
            arm_group.setPoseTarget(cur_start_pose);
            arm_group.setMaxAccelerationScalingFactor(0.2);
            arm_group.setMaxVelocityScalingFactor(0.2);
            //进行运动规划，计算机器人移动到目标的运动轨迹,此时只计算出轨迹，并不会控制机械臂运动
            //对应moveit中的plan按钮
            plan_move_use = plan_move_init;
            success_plan = arm_group.plan(plan_move_use) == moveit::planning_interface::MoveItErrorCode::SUCCESS;;
            // moveit::planning_interface::MoveItErrorCode success_plan = arm_group.plan(plan_move_use);
            ROS_INFO("Visualizing plan 2 (pose goal) %s",success_plan?"":"FAILED"); 
            //让机械臂按照规划的轨迹开始运动
            //对应moveit中的execute按钮
            if(success_plan)
                arm_group.execute(plan_move_use);
            sleep(1);
            //松开夹爪，准备进行下一次抓取
            GripperOutput.rPR = 0;
            grip_Pub.publish(GripperOutput);
            sleep(1);
        }
        loop_rate.sleep();
        ros::spinOnce();
    }
    return 0;
}