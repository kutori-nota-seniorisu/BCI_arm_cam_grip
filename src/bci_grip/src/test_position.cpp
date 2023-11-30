#include <ros/ros.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

Mat src;
bool down = false;
Point prept = Point(-1, -1);
Point curpt = Point(-1, -1);
void on_mouse(int event, int x, int y, int flags, void* ustc)
{

	if (event == CV_EVENT_LBUTTONDOWN)    //右键按下
	{
		prept = Point(x, y);
		cout << x << " " << y << endl;
		down = true;
	}
	else if (event == CV_EVENT_LBUTTONUP)     //右键放开
		down = false;

	if (down == true && event == CV_EVENT_MOUSEMOVE)    //右键按下且鼠标移动
	{
		curpt = Point(x, y);
		line(src, prept, curpt, Scalar(255, 0, 0), 5);
		waitKey(5);        //可以解决画图时卡顿的问题
		imshow("src", src);
		prept = curpt;
	}
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test_pos");
	src = imread("/home/sd/BCI_arm_cam_grip/src/bci_grip/src/pic/imgcolor000.jpg", 1);

	namedWindow("src");
	cvSetMouseCallback("src", on_mouse, 0);//关键内置函数

	imshow("src", src);

    cv::Mat Img, Img1, img_hsv, erode_hsv, inRange_hsv, dialationImage;
    int height = src.rows;//row表示行，rows表示行的总数，即图像的高
	int width = src.cols;//col表示列，cols表示列的总数，即图像的宽
    //cout << height << " " << width << endl;
    resize(src, Img, cv::Size(width, height)); //Size(1280,720)缩放后的图片尺寸
    //resize(dep_image, Img1, cv::Size(width, height));
    //namedWindow("pic_win1", 0);
    //imshow("pic_win1", Img);

    //蓝
	cv::Scalar blue_scalarL = cv::Scalar(60, 150, 46);
	cv::Scalar blue_scalarH = cv::Scalar(124, 255, 255);

    cv::Mat dst1, dst2, dst;
	//blur(Img, dst1, Size(5, 5), Point(-1, -1), 4);
	//GaussianBlur(Img, dst2, Size(15, 15), 15, 0, 4);
	GaussianBlur(Img, dst, cv::Size(5, 5), 25, 0, 4);
    //imshow("gaussian blur", dst);

    cvtColor(dst, img_hsv, cv::COLOR_BGR2HSV);
    imshow("hsv", img_hsv);

    //蓝
	cv::inRange(img_hsv, blue_scalarL, blue_scalarH, inRange_hsv);
    cv::imshow("inRange_hsv", inRange_hsv);
    
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));//size(5,5)是马赛克的矩形的大小
    cv::dilate(inRange_hsv, dialationImage, element);
    cv::erode(dialationImage, erode_hsv, element);
    cv::imshow("erode_hsv", erode_hsv);

    std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(erode_hsv, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat drawing = cv::Mat::zeros(erode_hsv.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++)
    {
        //Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//任意值
        cv::Scalar color = cv::Scalar(255, 182, 193);
        cv::drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
    }
    cv::imshow("contours", drawing);

	int min_area = 2000, index = 0;
    double imagearea;
    std::vector<double> PositionLength_Array, Point_Array;
    PositionLength_Array.clear();
    Point_Array.clear();
    std::vector<double> nowUrPose;
    double angle;
    for (int i = 0; i < contours.size(); i++)
    {
        imagearea = cv::contourArea(contours[i]);
        if (imagearea > min_area)
        {
            cv::RotatedRect rrect = minAreaRect(contours[i]);
            cv::Point2f points[4];
            rrect.points(points);   //读取最小外接矩形的四个顶点
            cv::Point2f cpt = rrect.center;
            ROS_INFO("%f, %f", cpt.x, cpt.y);
            //绘制旋转矩形与中心位置
            for(int j = 0; j < 4 ; j++)
            {
                if(j == 3)
                {
                    cv::line(Img, points[j], points[0], cv::Scalar(0, 255, 0), 2, 8, 0);
                    break;
                }
                cv::line(Img, points[j], points[j + 1], cv::Scalar(0, 255, 0), 2, 8, 0);
            }
            //绘制矩形中心
            cv::circle(Img, cpt, 2, cv::Scalar(0, 255, 0), 2, 8, 0);
            
            double length = 1000;
            for(int j = 0 ; j < 4 ; j++)
            {//取四边形最短的边长为按钮标记边长
                double l;
                l = sqrt((points[(j + 1)%4].x - points[j %4].x) * (points[(j + 1)%4].x - points[j % 4].x) +(points[(j + 1) % 4].y - points[j % 4].y) *(points[(j + 1) % 4].y - points[j % 4].y) );
                if (l < length)
                    length = l;
           }
           PositionLength_Array.push_back(length);
        }
    }

	waitKey(0);
	return 0;
}