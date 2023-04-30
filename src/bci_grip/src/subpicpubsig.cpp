#include "bci_grip/subpicpubsig.h"
//相机内参(待修正)
const double camera_factor = 100; 
const double camera_cx = 312.72546386;
const double camera_cy = 231.788;
const double camera_fx = 602.482;
const double camera_fy = 601.534;
void subpicpubsiger::callback(const sensor_msgs::ImageConstPtr& depth_img, const sensor_msgs::ImageConstPtr& color_img)
{
    ROS_WARN("%s", depth_img->encoding.c_str());
    
    color_ptr = cv_bridge::toCvCopy(color_img, sensor_msgs::image_encodings::BGR8);
    color_pic = color_ptr->image;
    depth_ptr = cv_bridge::toCvCopy(depth_img, sensor_msgs::image_encodings::TYPE_32FC1);
    depth_pic = depth_ptr->image;
    fs++;
    //ROS_INFO("%d", fs);
    subpicpubsiger::process_pic(color_pic);
}

subpicpubsiger::subpicpubsiger() : it(nh)
{
    num = 0;
    flag = 0;
    fs = 0;
    depth_sub.subscribe(nh, "/camera/aligned_depth_to_color/image_raw", 1);
    image_sub.subscribe(nh, "/camera/color/image_raw", 1);
    
    PicProcessedSig_Sub = nh.subscribe<std_msgs::Bool>("/PicSubSig", 1, &subpicpubsiger::PicProcessedSigCallback, this);
    sig_process = nh.advertise<std_msgs::Bool>("/PicSubSig", 1);
    //Picture_Pub = nh.advertise<std_msgs::Float64MultiArray>("PictureNode", 10);
    Picture_Pub = it.advertise("/PictureNode", 1);
    PositionLength_Pub = nh.advertise<std_msgs::Float64MultiArray>("/PositionLengthNode", 10);
    Point_Pub = nh.advertise<std_msgs::Float64MultiArray>("/Point3D", 10);
    //回调
    sync_.reset(new Sync(MySyncPolicy(1), depth_sub, image_sub));
    
    sync_->registerCallback(boost::bind(&subpicpubsiger::callback, this, _1, _2));
    //定义手眼标定矩阵
    hand_eye << 1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0;
                                0, 0, 0, 1;
    //ROS_INFO("Done!");
}

void subpicpubsiger::PicProcessedSigCallback(const std_msgs::Bool::ConstPtr& MsgPtr)
{
    if(MsgPtr->data == 1)     //订阅到信号处理节点发来的消息，识别到“注视准备区域”
    {
        ROS_INFO("图像已处理完毕，可以发布图片至PTB");
        flag = 1;
    }
    else
    {
        ROS_INFO("图像处理未完成……");
    }
}

void subpicpubsiger::process_pic(cv::Mat color_image)
{
    ROS_INFO("yeah!");
    cv::Mat Img, Img1, img_hsv, erode_hsv, inRange_hsv, dialationImage;
    int height = color_image.rows;//row表示行，rows表示行的总数，即图像的高
	int width = color_image.cols;//col表示列，cols表示列的总数，即图像的宽
    //cout << height << " " << width << endl;
    resize(color_image, Img, cv::Size(640, 480)); //Size(1280,720)缩放后的图片尺寸
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
    for (int i = 0; i < contours.size(); i++)
    {
        imagearea = cv::contourArea(contours[i]);
        if (imagearea > min_area)
        {
            cv::RotatedRect rrect = minAreaRect(contours[i]);
            cv::Point2f points[4];
            rrect.points(points);   //读取最小外接矩形的四个顶点
            cv::Point2f cpt = rrect.center;
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
            //将图像中物块的位置及边长存储到PositionLength_Array中
            PositionLength_Array.push_back(cpt.x);
            PositionLength_Array.push_back(cpt.y);
            //计算图像中物块中心点实际空间位置
            geometry_msgs::Point p, Point_Msg;
            if(depth_pic.ptr<float>(int(cpt.x))[int(cpt.y)] >0 &&  depth_pic.ptr<float>(int(cpt.x))[int(cpt.y)] <= 4096){
                float d = depth_pic.ptr<float>(int(cpt.x))[int(cpt.y)];//ushort d = depth_pic.ptr<ushort>(m)[n];
                p.z = double(d) / camera_factor;
                p.x = (int(cpt.y) - camera_cx) * p.z / camera_fx;
                p.y = (int(cpt.x) - camera_cy) * p.z / camera_fy;
                Eigen::Matrix<double, 4, 1>  Pt_Camera, Pt_Base;
                Pt_Camera << p.x, p.y, p.z, 1.0;
                Pt_Base = hand_eye * Pt_Camera;
                Point_Array.push_back(Pt_Base(0, 1));
                Point_Array.push_back(Pt_Base(1, 1));
                Point_Array.push_back(Pt_Base(2, 1));
            }
            
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
    cv::imshow("snack", Img);
    

    int key;
    bool sig = 0;
    std::string strnum, strname;
    std::stringstream ss;
    std::string strimg1_1 = "./src/bci_grip/src/pic/imgcolor00";
    std::string strimg2 = ".jpg";
    const char* pcname; //指向文件名称的首地址 

    //当接收到信号时，将图片发布给matlab的PTB
    if(flag == 1)
    {
        Pic_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", Img).toImageMsg();
        // std::vector<double> sendPic_reshape;
        // if (Img.isContinuous())     //判断内存是否连续
        // {
        //     sendPic_reshape.assign(Img.datastart, Img.dataend);
        // }
        // else
        // {
        //     for (int i = 0; i < Img.rows; ++i)
        //     {
        //         sendPic_reshape.insert(sendPic_reshape.end(), Img.ptr<double>(i), Img.ptr<double>(i)+Img.cols);
        //     }
        // }
        // std_msgs::Float64MultiArray pic;
        std_msgs::Float64MultiArray PositionLength_Msg, Point_Msg;
       	//pic.data = sendPic_reshape;
        Picture_Pub.publish(Pic_msg);
        ROS_INFO("图像已发布");
        PositionLength_Msg.data = PositionLength_Array;
        PositionLength_Pub.publish(PositionLength_Msg);
        ROS_INFO("位置大小信息已发布");
        Point_Msg.data = Point_Array;
        Point_Pub.publish(Point_Msg);
        ROS_INFO("点坐标已发布");
    }

    key = cv::waitKey(2);
    if(key == 32)
    {
        //sig = 1;
        //sigmsg.data = sig;
        ss.clear();
        ss << num;
        ss >> strnum;
        num++;  //保存图片的数目
        strname = strimg1_1 + strnum + strimg2;
        pcname = strname.data();
        imwrite(pcname, Img);
        //sig_process.publish(sigmsg);    //发布图像处理结束信号
    }
    color_pic.release();
    depth_pic.release();
    if(key == 113)
    {
        cv::destroyAllWindows();
    }
}