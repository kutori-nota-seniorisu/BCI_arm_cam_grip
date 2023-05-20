#ifndef _SUBPICPUBSIG_H
#define _SUBPICPUBSIG_H

#include <ros/ros.h>
//时间同步
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <image_transport/image_transport.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <cv_bridge/cv_bridge.h>

#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64MultiArray.h>
#include <sensor_msgs/CameraInfo.h> 
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Point.h>

#include <iostream>
#include <vector>
#include <Eigen/Dense>

#include <ur_rtde/rtde_receive_interface.h>
#include <ur_rtde/rtde_control_interface.h>

class subpicpubsiger
{
    private:
        ros::NodeHandle nh;
        message_filters::Subscriber<sensor_msgs::Image> depth_sub;
        message_filters::Subscriber<sensor_msgs::Image> image_sub;
        ros::Publisher sig_process;
        ros::Subscriber PicProcessedSig_Sub;
        ros::Subscriber camerainfo_Sub;
        ros::Subscriber GripSig1;
        int fs;//定义处理图像的频率
        int num;    //储存图片的数目
        bool flag;
        bool flag1;     //是否可进行下次抓取
        typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;   //时间戳对齐规则
        typedef message_filters::Synchronizer<MySyncPolicy> Sync;
        boost::shared_ptr<Sync> sync_;//时间同步器
        cv_bridge::CvImagePtr color_ptr, depth_ptr;
        cv::Mat color_pic, depth_pic;
        Eigen::Matrix<double, 4, 4> hand_eye;
    
    public:
        std_msgs::Bool sigmsg;
        //ros::Publisher Picture_Pub;
        ros::Publisher PositionLength_Pub;
        ros::Publisher Point_Pub;
        image_transport::ImageTransport it;
        image_transport::Publisher Picture_Pub;
        sensor_msgs::ImagePtr Pic_msg;
        geometry_msgs::Point Pt_msg;
        subpicpubsiger();
        void process_pic(cv::Mat color_image);
        void callback(const sensor_msgs::ImageConstPtr& depth_img, const sensor_msgs::ImageConstPtr& color_img);
        void PicProcessedSigCallback(const std_msgs::Bool::ConstPtr& MsgPtr);
        void GripSigCallback(const std_msgs::Bool::ConstPtr& MsgPtr);
        // ur_rtde::RTDEControlInterface rtde_control;
        // ur_rtde::RTDEReceiveInterface rtde_receive;
};



#endif