#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64MultiArray.h>
#include <sensor_msgs/Image.h>
#include <iostream>
#include <vector>



int main(int argc, char** argv){
    ros::init(argc, argv, "testpic_pub");
    ros::NodeHandle n;
    ros::Rate loop_rate(0.1);
    image_transport::ImageTransport it(n);
    cv::Mat img = cv::imread("/home/sd/catkin_ws/src/bci_grip/src/1.png", cv::IMREAD_COLOR);    
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img).toImageMsg();
    image_transport::Publisher pub = it.advertise("/PictureNode", 1);

    cv::imshow("pic", img);
    while(ros::ok()){

        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

