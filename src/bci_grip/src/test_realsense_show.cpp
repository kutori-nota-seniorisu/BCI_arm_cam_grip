/*
本程序展示realsense相机使用的基本操作——实时显示彩色RGB图片及配准的深度信息
*/
#include <ros/ros.h>

#include<iostream>
#include <vector>
#include <Eigen/Dense>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <cv_bridge/cv_bridge.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <std_msgs/Int8.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64MultiArray.h>
#include <sensor_msgs/CameraInfo.h> 
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Point.h>



using namespace std;
using namespace cv;

//相机内参，切换相机时应注意修改此处参数
const double camera_factor = 1000; 
const double camera_cx = 326.3896484375;
const double camera_cy = 245.33595275878906;
const double camera_fx = 621.5462646484375;
const double camera_fy = 621.89404296875;

class showpic
{
    private:
        ros::NodeHandle nh;
        message_filters::Subscriber<sensor_msgs::Image> depth_sub;
        message_filters::Subscriber<sensor_msgs::Image> image_sub;
        ros::Subscriber camerainfo_Sub;
        int fs;//定义处理图像的频率
        int num;    //储存图片的数目
        bool flag;
        typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;   //时间戳对齐规则
        typedef message_filters::Synchronizer<MySyncPolicy> Sync;
        boost::shared_ptr<Sync> sync_;//时间同步器
        cv_bridge::CvImagePtr color_ptr, depth_ptr;
        cv::Mat color_pic, depth_pic;
    
    public:
        std_msgs::Bool sigmsg;
        //ros::Publisher Picture_Pub;
        ros::Publisher PositionLength_Pub;
        ros::Publisher Point_Pub;
        image_transport::ImageTransport it;
        image_transport::Publisher Picture_Pub;
        sensor_msgs::ImagePtr Pic_msg;
        geometry_msgs::Point Pt_msg;
        showpic();
        void show_pic(cv::Mat color_image);
        void callback(const sensor_msgs::ImageConstPtr& depth_img, const sensor_msgs::ImageConstPtr& color_img);
};

void showpic::callback(const sensor_msgs::ImageConstPtr& depth_img, const sensor_msgs::ImageConstPtr& color_img)
{
    ROS_WARN("%s", depth_img->encoding.c_str());
    
    color_ptr = cv_bridge::toCvCopy(color_img, sensor_msgs::image_encodings::BGR8);
    color_pic = color_ptr->image;
    depth_ptr = cv_bridge::toCvCopy(depth_img, sensor_msgs::image_encodings::TYPE_32FC1);
    depth_pic = depth_ptr->image;
    fs++;
    showpic::show_pic(color_pic);
}

showpic::showpic() : it(nh)
{
    num = 0;
    flag = 0;
    fs = 0;
    depth_sub.subscribe(nh, "/camera/aligned_depth_to_color/image_raw", 1);
    image_sub.subscribe(nh, "/camera/color/image_raw", 1);
    //回调
    sync_.reset(new Sync(MySyncPolicy(1), depth_sub, image_sub));
    sync_->registerCallback(boost::bind(&showpic::callback, this, _1, _2));
}

void showpic::show_pic(cv::Mat color_image)
{
    cv::Mat Img;
    int height = color_image.rows;//row表示行，rows表示行的总数，即图像的高
	int width = color_image.cols;//col表示列，cols表示列的总数，即图像的宽
    resize(color_image, Img, cv::Size(width, height)); //Size(1280,720)缩放后的图片尺寸

    imshow("Img", Img);

    int key;
    key = cv::waitKey(2);

    color_pic.release();
    depth_pic.release();

    if(key == 113)
    {
        cv::destroyAllWindows();
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test_realsense_show");
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
    showpic sp;
    cout<<"hh"<<endl;
    ros::spin();
}