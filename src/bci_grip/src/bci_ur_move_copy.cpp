#include <string>
#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float64.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Bool.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <robotiq_2f_gripper_control/Robotiq2FGripper_robot_output.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <ur_rtde/rtde_control_interface.h>
#include <tf2_ros/transform_listener.h>

using namespace ur_rtde;
// using namespace std;

# define USE_UR_SIM 0
#if USE_UR_SIM
RTDEControlInterface rtde_control("127.0.0.1");
//ur_rtde::RTDEReceiveInterface rtde_receive("127.0.0.1");
#else
RTDEControlInterface rtde_control("192.168.0.1");
ur_rtde::RTDEReceiveInterface rtde_receive("192.168.0.1");
#endif

#define CTRL_FREQ 128

typedef struct {
  Eigen::Matrix<double,6,1> pose;
  Eigen::Matrix<double,6,1> speed;
  Eigen::Matrix<double,6,1> accel;
  Eigen::Matrix<double,6,1> force;
}Status_Cart;

bool flag =  0; //是否接收到相机开启的信号
Eigen::MatrixXd PosLen;    //用来存储接收到的物块位姿信息
Eigen::MatrixXd Point3D;
int result;
int len;

void PosLenCallback(const std_msgs::Float64MultiArray::ConstPtr& msg) {
	
	std::vector<double> pos_len = msg->data;
	ROS_INFO("I heard Position and Length!");
	len = msg->data.size();
	PosLen = Eigen::Map<Eigen::MatrixXd> (pos_len.data(), len / 3, 3);
}

void ResultCallback(const std_msgs::UInt16::ConstPtr& msg) {
	ROS_INFO("I heard Result : %d!", msg->data);
	flag = 1;
	result = msg->data;
}

void PointCallback(const std_msgs::Float64MultiArray::ConstPtr& msg) {
	int len;
	std::vector<double> pt_3D = msg->data;
	ROS_INFO("I heard Result Point3D!  %f, %f, %f, %f, %f, %f, %d", pt_3D[0], pt_3D[1], pt_3D[2], pt_3D[3], pt_3D[4], pt_3D[5], msg->data.size());
	len = msg->data.size();
	Point3D = Eigen::Map<Eigen::MatrixXd> (&pt_3D[0], 3, len / 3);
}

//旋转矢量到四元数
Eigen::Quaterniond rotationVector_quaternion(Eigen::Matrix<double,3,1> rotationVector) {
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
Eigen::Vector3d  rotationMatrix_RPY(Eigen::Matrix3d rotationMatrix) {
	return rotationMatrix.eulerAngles(2, 1, 0);
}

//旋转矩阵转换为旋转矢量
Eigen::Vector3d rotationMatrix_Vec(Eigen::Matrix3d rotation_matrix) {
	Eigen::AngleAxisd rotation_vector(rotation_matrix);
	Eigen::Vector3d rot_vec(rotation_vector.angle() * rotation_vector.axis());
	return rot_vec;
}

//四元数转换为旋转矩阵
Eigen::Matrix3d quaternion_rotationMatrix(Eigen::Quaterniond quaternion)
{
  return quaternion.toRotationMatrix();
}

//获取基座标系base下末端坐标系tool0的位置pose_t和姿态pose_r（旋转矩阵）
int getPose(const tf2_ros::Buffer &tfBuffer_, Eigen::VectorXd &pose_t, Eigen::Matrix3d &pose_r)
{
	std::vector<double> nowUrPose;
	nowUrPose = rtde_receive.getActualTCPPose();
	pose_t = Eigen::Map<Eigen::Matrix<double,3,1>>(&nowUrPose[0],3);
	Eigen::Matrix<double,3,1> tmpDatar;
	tmpDatar = Eigen::Map<Eigen::Matrix<double,3,1>>(&nowUrPose[3],3);
	Eigen::Quaterniond quaternion=rotationVector_quaternion(tmpDatar);
	pose_r=quaternion_rotationMatrix(quaternion);
	Eigen::Matrix<double,3,1> tmpDatar1;
	std::cout << "pose_r" << pose_r << std::endl;


   //joint
	std::vector<double> nowUrjoint;
	nowUrjoint = rtde_receive.getActualQ();
	Eigen::VectorXd joint;
	joint = Eigen::Map<Eigen::Matrix<double,6,1>>(&nowUrjoint[0], 6);
	std::cout << "joint:" << joint << std::endl;
	return 0;
}

int main(int argc, char** argv) {
	//ros初始化
	ros::init(argc, argv, "bci_ur_actual_copy");
	ros::NodeHandle n;
	ros::Publisher GripSigPub = n.advertise<std_msgs::Bool>("/GripSig", 50);
	ros::Publisher GripSigPub1 = n.advertise<std_msgs::Bool>("/GripSig1", 1);
	std_msgs::UInt16 GripSigMsg;
	std_msgs::Bool GripSigMsg1;
	ros::Subscriber PositionLength_Sub = n.subscribe("/PositionLengthNode", 10, &PosLenCallback);
	ros::Subscriber Result_Sub = n.subscribe("/ResultNode", 10, &ResultCallback);
	ros::Subscriber Point_Sub = n.subscribe("/Point3D", 1, &PointCallback);

	tf2_ros::Buffer tfBuffer;
	tf2_ros::TransformListener tfListener(tfBuffer);  //获取机械臂末端在基坐标系下的位姿

	ros::Rate loop_rate(CTRL_FREQ);


	ros::AsyncSpinner AS(1);
	AS.start();

	double speed=0.005;
	double acceleration=0.001;

	setlocale(LC_CTYPE, "zh_CN.utf8");

	//初始化夹爪相关数据类型
	ros::Publisher grip_Pub = n.advertise<robotiq_2f_gripper_control::Robotiq2FGripper_robot_output>("/Robotiq2FGripperRobotOutput", 10);
	robotiq_2f_gripper_control::Robotiq2FGripper_robot_output GripperOutput;
	GripperOutput.rACT = 0;
	GripperOutput.rGTO = 1;
	GripperOutput.rATR = 0;
	GripperOutput.rPR = 0;      //0时打开，255时完全闭合
	GripperOutput.rSP = 255;
	GripperOutput.rFR = 150;
	grip_Pub.publish(GripperOutput);
	sleep(2);
	GripperOutput.rACT = 1;
	GripperOutput.rGTO = 1;
	GripperOutput.rATR = 0;
	GripperOutput.rPR = 0;      //0时打开，255时完全闭合
	GripperOutput.rSP = 255;
	GripperOutput.rFR = 150;
	grip_Pub.publish(GripperOutput);
	sleep(2);
	Eigen::Matrix3d pose_r = Eigen::MatrixXd::Zero(3, 3);						//本周期获取的姿态
	Eigen::VectorXd pose_t = Eigen::MatrixXd::Zero(3, 1);						//理想位置

	//五个物块序号对应的闪烁频率
	int fre[5] = {9, 10, 11, 12, 13};

	/**************这一步，先运动到物块上方****************/
	//定义机器人初始位姿，速度
	std::vector<double> initPose = {0.200000, -0.499992, 0.300033,  -0.000153, 3.140025, -0.000192};
	std::vector<double> endPose1 = {0.213563, -0.303634, 0.091221,  -0.000080, 3.140102, -0.000093};
	std::vector<double> endPose2 = {0.213563, -0.303634, 0.191221,  -0.000080, 3.140102, -0.000093};
	std::vector<double> endPose3_1 = {0.213563, -0.303634, 0.11221,  -0.000080, 3.140102, -0.000093};
	std::vector<double> endPose3_2 = {0.163563, -0.303634, 0.11221,  -0.000080, 3.140102, -0.000093};
	std::vector<double> endPose3_3 = {0.253563, -0.303634, 0.11221,  -0.000080, 3.140102, -0.000093};
	std::vector<double> pose;
	Status_Cart status;
	status.pose << Eigen::Map<Eigen::MatrixXd>(&initPose[0], 6, 1);
	status.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
   
	//等待机器人到达初始位姿
	rtde_control.servoL(initPose, speed, acceleration, 1,  0.03, 600);
	sleep(4);
	// usleep(3000);

	int num = 0;
	while(ros::ok()) {
		Eigen::Matrix<double,4,4> T_robot_flange;
		T_robot_flange << -1, 0, 0, 0.2, 
						   0, 1, 0, -0.5, 
						   0, 0, -1, 0.3,
						   0, 0, 0, 1;
		//getPose(tfBuffer, pose_t, pose_r);
		//T_robot_flange << pose_r, pose_t, 0, 0, 0, 1;
		//ROS_INFO("flag : %d", flag);
		//当获取到相机发布的位姿信息后，只需要将信息存储，当接收到分析结果时，开始进行轨迹规划并运动
		if(flag) {
			num++;
			//结果是第i个物块
			int i;
			for (i = 0 ; i < 5 ; i++) {
				if(result == fre[i])
					break;
			}
			ROS_INFO("I = %d", i);
			if(i >= len / 3)
				continue;

			//目标抓取姿态为绕x轴旋转180度，gripPose与rotVec均未用到
			Eigen::Matrix3d gripPose;
			Eigen::Vector3d rotVec;
			gripPose << 1, 0, 0,
						0, -1, 0,
						0, 0, -1;
									  
			rotVec = rotationMatrix_Vec(gripPose);

			Eigen::Matrix<double, 4, 1>  Pt_TCL, Pt_Base;
			Pt_TCL  << Point3D(0, i), Point3D(1, i), Point3D(2, i), 1.0;
			
			ROS_INFO("Pt_TCL : %f, %f, %f", Pt_TCL(0, 0), Pt_TCL(1, 0), Pt_TCL(2, 0));     
			Pt_Base = T_robot_flange * Pt_TCL;
			// status这个变量没有用到
			status.pose << Pt_Base(0, 0) , Pt_Base(1, 0), Pt_Base(2, 0) + 0.2,
											0, 3.14, 0;
			pose.clear();
			pose = {Pt_Base(0, 0) , Pt_Base(1, 0), Pt_Base(2, 0) + 0.17, 0, 3.14, 0};
			ROS_INFO("Pose: %d, %d, %d", pose[0], pose[1], pose[2]);
			ROS_INFO("Pt_Base : %d, %d, %d", Pt_Base(0,0), Pt_Base(1, 0), Pt_Base(2, 0)); 
			rtde_control.servoL(pose, speed, acceleration, 2,  0.1, 1000);
			sleep(4);
			
			ROS_INFO("已到达目标物体上方！");

			//关闭夹爪
			GripperOutput.rPR = 250;
			grip_Pub.publish(GripperOutput);
			sleep(1);
			ROS_INFO("夹爪已闭合，将回到初始位置！");
			//回到初始点处
			status.pose << Eigen::Map<Eigen::MatrixXd>(&initPose[0], 6, 1);
			rtde_control.servoL(initPose, speed, acceleration, 2,  0.1, 1000);
			sleep(2);

			//将物块放到最终的位置
			rtde_control.servoL(endPose2, speed, acceleration, 2,  0.1, 1000);
			sleep(2);
			if(num % 3 == 1)
			{
				rtde_control.servoL(endPose3_1, speed, acceleration, 2,  0.1, 1000);
				sleep(2);
			}
			else if(num % 3 == 2)
			{
				rtde_control.servoL(endPose3_2, speed, acceleration, 2,  0.1, 1000);
				sleep(2);
			}
			else if(num % 3 == 0)
			{
				rtde_control.servoL(endPose3_3, speed, acceleration, 2,  0.1, 1000);
				sleep(2);
			}
			//松开夹爪，准备进行下一次抓取
			GripperOutput.rPR = 0;
			grip_Pub.publish(GripperOutput);
			sleep(1);

			//回到初始点处 
			status.pose << Eigen::Map<Eigen::MatrixXd>(&initPose[0], 6, 1);
			rtde_control.servoL(initPose, speed, acceleration, 2,  0.1, 1000);
			sleep(5);
			ROS_INFO("已回到初始位置，打开夹爪准备下一次抓取！");

			GripSigMsg1.data = 1;
			GripSigPub1.publish(GripSigMsg1);
			//抓取结束，发布可进行下一次抓取的信号
			for (int j = 0 ; j < 3 ; j++)
			{
				GripSigMsg.data = 1;
				GripSigPub.publish(GripSigMsg);
				ROS_INFO("抓取结束，发布了可进行下一次抓取的信号！");
				sleep(1);
			}

			
			flag = 0;
		}
		loop_rate.sleep();
		ros::spinOnce();
	}
	return 0;
}