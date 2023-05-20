#include <string>
#include <ros/ros.h>
#include "std_msgs/String.h" //所要订阅的消息类型，此处是std_msgs包下的String。msg
#include "std_msgs/Float32.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <moveit/move_group_interface/move_group_interface.h>

// arm.getCurrentPose 与 arm.setPoseTarget--- x、y、z + 四元数 geometry_msgs::PoseStamped cur_start_pos
// arm.getCurrentJointValues 与 arm.setCurrentJointValues--- 六个关节角数值 std::vector<double> a(6)

std::stringstream ur5_mgs;
bool flag = 0;
static ros::Subscriber ur5_sub;

void UR5Move_Callback(const std_msgs::String::ConstPtr &msg)
{
    flag = 1;
    ur5_mgs.clear();
    ur5_mgs.str("");
    ur5_mgs << msg->data.c_str();
    ROS_INFO("I heard: [%s]", msg->data.c_str()); //将接收到的消息打印出来
}

int main(int argc, char **argv)
{
    //初始化节点
	ros::init(argc, argv, "ur5go_home_up");
    ros::NodeHandle node_handle; 
    //引入多线程
	ros::AsyncSpinner spinner(1);
    //开启多线程
	spinner.start();

    //初始化需要使用 move_group 控制的机械臂中的 arm_group
    //对应moveit中选择的规划部分
    moveit::planning_interface::MoveGroupInterface arm_group("manipulator");

    //获取终端 link 的名称
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
    //ROS_INFO(default_set[0],default_set[1]);
    std_msgs::String movemsg;
    ur5_sub = node_handle.subscribe("/ur5_topic", 3, UR5Move_Callback);
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        if(flag){
            flag = 0;
            movemsg.data = ur5_mgs.str();
            //控制机械臂先回到"up"的位置状态
            arm_group.setStartStateToCurrentState();
            arm_group.setNamedTarget(movemsg.data);
            ROS_INFO("Let's go [%s]!", movemsg.data.c_str());
            arm_group.move(); //规划＋运动
            sleep(3);

            // 控制机械臂先回到初始化位置
            //arm_group.setNamedTarget("home");
            //arm_group.setMaxAccelerationScalingFactor(0.1);
            //arm_group.setMaxVelocityScalingFactor(0.1);
            //ROS_INFO("Let's go home~");
            //arm_group.move();
            //sleep(2);
        }
        ros::spinOnce();    
    }
	return 0;
}