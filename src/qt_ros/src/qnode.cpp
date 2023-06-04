/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/UInt16.h>
#include <sstream>
#include <QDebug>
#include <QFile>
#include "../include/qt_ros/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_ros
{

	/*****************************************************************************
	** Implementation
	*****************************************************************************/

	QNode::QNode(int argc, char **argv) : init_argc(argc),
										  init_argv(argv)
	{
	}

	QNode::~QNode()
	{
		if (ros::isStarted())
		{
			ros::shutdown(); // explicitly needed since we use ros::start();
			ros::waitForShutdown();
		}
		wait();
	}

	bool QNode::init()
	{
		ros::init(init_argc, init_argv, "qt_ros");
		if (!ros::master::check())
		{
			return false;
		}
		ros::start(); // explicitly needed since our nodehandle is going out of scope.
		ros::NodeHandle n;
		// 发布者，发布采样频率
        pub_rate = n.advertise<std_msgs::UInt16>("samplerate", 10);
		// 发布者，发布数据包
        pub_packet = n.advertise<std_msgs::Float32MultiArray>("packet", 1000);
		//	start();
		return true;
	}

    // 发布者，发布采样频率
    void QNode::QNode_Pub_Rate(int nSampleRate)
	{
		std_msgs::UInt16 msg;
		msg.data = nSampleRate;
		ROS_INFO("I pub rate uint16 data: %u", msg.data);
        pub_rate.publish(msg);
	}

	// 发布者，发布数据包
    void QNode::QNode_Pub_Packet(float *pfData, int nChannels, long nSamples)
	{
		std::vector<float> vEegData(pfData, pfData + nChannels * nSamples);
        // for (int i = 0; i < nChannels; ++i)
        //     qDebug() << "eegdata " << i << " is " << vEegData[i];
        std_msgs::Float32MultiArray msg;
		msg.data = vEegData;
        ROS_INFO("I pub packet data");
        pub_packet.publish(msg);
	}
} // namespace qt_ros
