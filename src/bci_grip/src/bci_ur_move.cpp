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

bool flag =  0; //是否接收到相机开启的信号
Eigen::MatrixXd PosLen;    //用来存储接收到的物块位置与最短边边长信息
Eigen::MatrixXd Point3D;
int result;
int len;
bool isempty = true;

void PosLenCallback(const std_msgs::Float64MultiArray::ConstPtr& msg) {
	
	std::vector<double> pos_len = msg->data;
	ROS_INFO("我获得了所有物块的位置与最短边边长信息！！");
	// len = msg->data.size();
	// PosLen = Eigen::Map<Eigen::MatrixXd> (pos_len.data(), 3, len / 3);
}

void ResultCallback(const std_msgs::UInt16::ConstPtr& msg) {
	ROS_INFO("我获得了分析结果: %d!", msg->data);
	flag = 1;
	result = msg->data;
}

void PointCallback(const std_msgs::Float64MultiArray::ConstPtr& msg) {
	// int len;
	std::vector<double> pt_3D = msg->data;
	for (auto it = pt_3D.begin(); it != pt_3D.end(); ++it) {
        std::cout << *it << " "; // 输出当前元素值
    }
	std::cout << std::endl;
	// ROS_INFO("I heard Result Point3D!  %f, %f, %f, %f, %f, %f, %d", pt_3D[0], pt_3D[1], pt_3D[2], pt_3D[3], pt_3D[4], pt_3D[5], msg->data.size());
	if(!pt_3D.empty()) {
		isempty = false;
		len = msg->data.size();
		Point3D = Eigen::Map<Eigen::MatrixXd> (&pt_3D[0], 4, len / 4);
		std::cout << Point3D(0, 0) << " " << Point3D(1, 0) << " " << Point3D(2, 0) << " " << Point3D(3, 0) << std::endl; 
		std::cout << Point3D(0, 1) << " " << Point3D(1, 1) << " " << Point3D(2, 1) << " " << Point3D(3, 1) << std::endl; 
		std::cout << Point3D(0, 2) << " " << Point3D(1, 2) << " " << Point3D(2, 2) << " " << Point3D(3, 2) << std::endl; 
	}
	else {
		isempty = true;
	}
}

int main(int argc, char** argv) {
	//ros初始化
	ros::init(argc, argv, "bci_ur_actual");
	ros::NodeHandle n;
	ros::Publisher GripSigPub = n.advertise<std_msgs::Bool>("/GripSig", 50);
	ros::Publisher GripSigPub1 = n.advertise<std_msgs::Bool>("/GripSig1", 1);
	std_msgs::UInt16 GripSigMsg;
	std_msgs::Bool GripSigMsg1;
	// 对应的publisher在 subpicpubsig.cpp 中，数据类型为 Float64MultiArray
	// 获得一个一维数组，数组中依次是：1号物块x坐标，1号物块y坐标，1号物块短边边长，2号物块x坐标，2号物块y坐标，2号物块短边边长…… 
	// 在此处使用了全局变量len来存储数组长度，使用了PosLen来存储话题数据
	ros::Subscriber PositionLength_Sub = n.subscribe("/PositionLengthNode", 10, &PosLenCallback);
	// 对应的publisher在 onlineanalysis.py 中，数据类型为 UInt16
	// 获得一个数字，是CCA分析结果
	ros::Subscriber Result_Sub = n.subscribe("/ResultNode", 10, &ResultCallback);
	// 对应的publisher在 subpicpubsig.cpp 中，数据类型为 Float64MultiArray
	// 获取了点云信息
	ros::Subscriber Point_Sub = n.subscribe("/Point3D", 1, &PointCallback);

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

	//五个物块序号对应的闪烁频率
	int fre[5] = {9, 10, 11, 12, 13};

	/**************这一步，先运动到物块上方****************/
	//定义机器人初始位姿，速度
	std::vector<double> initPose = {0.200000, -0.499992, 0.300033,  -0.000153, 3.140025, -0.000192};
	std::vector<double> endPose1 = {0.213563, -0.303634, 0.091221,  -0.000080, 3.140102, -0.000093};
	std::vector<double> endPose2 = {0.213563, -0.303634, 0.191221,  -0.000080, 3.140102, -0.000093};
	std::vector<double> endPose3 = {0.213563, -0.303634, 0.11221,  -0.000080, 3.140102, -0.000093};
	std::vector<double> pose;

   
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

		//当获取到相机发布的位姿信息后，只需要将信息存储，当接收到分析结果时，开始进行轨迹规划并运动
		if(flag && !isempty) {
			num++;
			//结果是第i个物块
			int i;
			// std::cout << Point3D(3, i)
			for (i = 0 ; i < 5 ; i++) {
				std::cout << Point3D(3, i) << std::endl;
				if(result == int(Point3D(3, i)))
					break;
			}
			ROS_INFO("结果是第%d个物块", i+1);

			// 若识别出的结果频率编号大于当前物块数，说明结果错误，不进行本次抓取
			std::cout << "i=" << i << std::endl;
			std::cout << "len=" << len << std::endl;
			if(i >= len / 4)	
			{
				flag = 0;
				continue;
			}
			std::cout << "i=" << i << std::endl;
			Eigen::Matrix<double, 4, 1>  Pt_TCL, Pt_Base;
			// Pt_TCL是齐次坐标
			Pt_TCL  << Point3D(0, i), Point3D(1, i), Point3D(2, i), 1.0;
			
			ROS_INFO("Pt_TCL : %f, %f, %f", Pt_TCL(0, 0), Pt_TCL(1, 0), Pt_TCL(2, 0));     
			Pt_Base = T_robot_flange * Pt_TCL;

			pose.clear();
			pose = {Pt_Base(0, 0) , Pt_Base(1, 0), Pt_Base(2, 0) + 0.17, 0, 3.14, 0};
			// 移动至目标物体上方
			rtde_control.servoL(pose, speed, acceleration, 2,  0.1, 1000);
			ROS_INFO("Pose: %d, %d, %d", pose[0], pose[1], pose[2]);
			ROS_INFO("Pt_Base : %d, %d, %d", Pt_Base(0,0), Pt_Base(1, 0), Pt_Base(2, 0)); 

			sleep(4);
			ROS_INFO("已到达目标物体上方！");

			//关闭夹爪
			GripperOutput.rPR = 250;
			grip_Pub.publish(GripperOutput);
			sleep(1);
			ROS_INFO("夹爪已闭合，将回到初始位置！");
			//回到初始点处
			rtde_control.servoL(initPose, speed, acceleration, 2,  0.1, 1000);
			sleep(2);

			//将物块放到最终的位置
			rtde_control.servoL(endPose2, speed, acceleration, 2,  0.1, 1000);
			sleep(2);
			rtde_control.servoL(endPose3, speed, acceleration, 2,  0.1, 1000);
			sleep(2);

			//松开夹爪，准备进行下一次抓取
			GripperOutput.rPR = 0;
			grip_Pub.publish(GripperOutput);
			sleep(1);

			//回到初始点处 
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