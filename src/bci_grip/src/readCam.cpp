#include <ros/ros.h>
#include"std_msgs/String.h"
#include<iostream>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/Int8.h>

using namespace std;
using namespace cv;


Mat img;
int rows, cols;
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        cv_bridge::CvImageConstPtr cv_ptr;
        cv_ptr = cv_bridge::toCvShare(msg, "bgr8");
        img = cv_ptr -> image;
        Mat img_temp = img.clone();
        imwrite("/home/code/bci_ws/src/img_.jpg", img_temp);

        Mat roi;
        Rect rect;
        cols = img_temp.cols;//2448
        rows = img_temp.rows;//2048
        ROS_INFO("Image size: %d, %d", cols, rows);
        rect = Rect(0, 0, cols, rows);
        roi = img_temp(rect);
        namedWindow("view", CV_WINDOW_NORMAL);
        resizeWindow("view", 960, 720);
        imshow("view", img_temp);
        waitKey(5);

    }
    catch(const std::exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
    
    
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "test");
    ros::NodeHandle n;
    image_transport::ImageTransport it(n);
    image_transport::Subscriber sub = it.subscribe("/camera/color/image_raw", 1, imageCallback);
    ros::spin();
    return 0;


}