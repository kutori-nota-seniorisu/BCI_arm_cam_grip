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
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include "bci_grip/subpicpubsig.h"

using namespace std;
using namespace cv;



int main(int argc, char** argv)
{
    ros::init(argc, argv, "col_align_dep");
    ros::NodeHandle n;
    cout<<"hh"<<endl;
    //需要将深度图和彩色图同步
    /*//depth_sub = n.subscribe<sensor_msgs::Image>("/camera/aligned_depth_to_color/image_raw", 10, DepthCallback);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub(n, "/camera/aligned_depth_to_color/image_raw", 1);
    message_filters::Subscriber<sensor_msgs::Image> image_sub(n, "/camera/image_raw", 1);
    //message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image> sync(depth_sub, image_sub, 10);
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;
    // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), depth_sub, image_sub);
    sync.registerCallback(boost::bind(&callback, _1, _2));*/
    subpicpubsiger sp;
    cout<<"hh"<<endl;
    ros::spin();
}