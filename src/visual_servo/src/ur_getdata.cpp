#include <Eigen/Geometry>
#include <ur_rtde/rtde_receive_interface.h>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde.h>
#include <ur_rtde/rtde_receive_interface_doc.h>
#include <ur_rtde/robot_state.h>
#include <ur_rtde/rtde_export.h>
#include <ur_rtde/rtde_utility.h>
#include <ur_rtde/rtde_io_interface.h>
#include <thread>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <ros/ros.h>
#include <vector>
#include <std_msgs/Float32.h>
#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace ur_rtde;
using namespace std;
using namespace Eigen;
using namespace cv;

RTDEControlInterface rtde_control("192.168.0.104");
ur_rtde::RTDEReceiveInterface rtde_receive("192.168.0.104");

// int main(int argc, char**argv)
// {
//     return 0;
// }






int main(int argc, char **argv)
{
    std::vector<double> nowUrPose;
    ros::init(argc, argv, "ur_getdata");
    ros::NodeHandle n;
    //ros::Publisher chatter_pub = n.advertise<visual_servo::circle>("chatter", 1000);
    //ros::Publisher pub = n.advertise<double>("position");
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        nowUrPose = rtde_receive.getActualTCPPose();
        ROS_INFO("x = %f, y = %f, z = %f,  rx = %f, ry = %f, rz = %f", nowUrPose[0], nowUrPose[1], nowUrPose[2], nowUrPose[3], nowUrPose[4], nowUrPose[5]);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;

}
