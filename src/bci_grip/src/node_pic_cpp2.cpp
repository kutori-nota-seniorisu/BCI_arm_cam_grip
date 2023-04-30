#include <ros/ros.h>
#include"std_msgs/String.h"
#include"std_msgs/Bool.h"
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

int main(int argc, char** argv)
{
    ros::init(argc, argv, "node_pic_cpp2");
    ros::NodeHandle n;

    Mat Img, img_hsv, erode_hsv, inRange_hsv, dialationImage;
    Mat img = imread("/home/edify-cx/code/bci_ws/src/bci_grip/src/2.jpg", -1);
    if(!img.data)
    {
        cout << "请输入正确的图像名称！" << endl;
        return -1;
    }
    int height = img.rows;//row表示行，rows表示行的总数，即图像的高
	int width = img.cols;//col表示列，cols表示列的总数，即图像的宽
    //cout << height << " " << width << endl;
    resize(img, Img, Size(width/3, height/3)); //Size(1280,720)缩放后的图片尺寸
    //namedWindow("pic_win1", 0);
    //imshow("pic_win1", Img);

    //蓝
	Scalar blue_scalarL = Scalar(60, 150, 46);
	Scalar blue_scalarH = Scalar(124, 255, 255);

    Mat dst1, dst2, dst;
	//blur(Img, dst1, Size(5, 5), Point(-1, -1), 4);
	//GaussianBlur(Img, dst2, Size(15, 15), 15, 0, 4);
	GaussianBlur(Img, dst, Size(5, 5), 25, 0, 4);
    //imshow("gaussian blur", dst);

    cvtColor(dst, img_hsv, COLOR_BGR2HSV);
    imshow("hsv", img_hsv);

    //蓝
	inRange(img_hsv, blue_scalarL, blue_scalarH, inRange_hsv);
    imshow("inRange_hsv", inRange_hsv);
    
    Mat element = getStructuringElement(MORPH_RECT, Size(2, 2));//size(5,5)是马赛克的矩形的大小
    dilate(inRange_hsv, dialationImage, element);
    erode(dialationImage, erode_hsv, element);
    imshow("erode_hsv", erode_hsv);

    vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(erode_hsv, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(erode_hsv.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++)
    {
        //Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//任意值
        Scalar color = Scalar(255, 182, 193);
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
    }
    imshow("contours", drawing);

	int min_area = 2000, index = 0;
    double imagearea;
    for (int i = 0; i < contours.size(); i++)
    {
        imagearea = contourArea(contours[i]);
        if (imagearea > min_area)
        {
            RotatedRect rrect = minAreaRect(contours[i]);
            Point2f points[4];
            rrect.points(points);   //读取最小外接矩形的四个顶点
            Point2f cpt = rrect.center;
            //绘制旋转矩形与中心位置
            for(int j = 0; j < 4 ; j++)
            {
                if(j == 3)
                {
                    line(Img, points[j], points[0], Scalar(0, 255, 0), 2, 8, 0);
                    break;
                }
                line(Img, points[j], points[j + 1], Scalar(0, 255, 0), 2, 8, 0);
            }
            //绘制矩形中心
            circle(Img, cpt, 2, Scalar(0, 255, 0), 2, 8, 0);
        }
    }
    imshow("snack", Img);

    waitKey(0);
    destroyAllWindows();
    return 0;
}