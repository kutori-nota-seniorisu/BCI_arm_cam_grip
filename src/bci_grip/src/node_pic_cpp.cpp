#include<librealsense2/rs.hpp>
#include<opencv2/opencv.hpp>

#include<fstream>
#include<iostream>
#include<sstream>

#include<unistd.h>

#include "ros/ros.h"

using namespace std;
using namespace cv;

#define RS_WIDTH 640//1280
#define RS_HEIGHT 480//720
#define RS_FPS 30

int main(int argc, char* argv[]) 
{
    ros::init(argc, argv, "node_pic_cpp");

    //首先判断设备是否存在
    rs2::context ctx;
    auto list = ctx.query_devices();    //Get a snapshot of currently connected devices
    if(list.size() == 0)
        throw std::runtime_error("No device detected!");
    rs2::device dev = list.front();     //"front" return the first element, "end" return the last element

    //Declare depth colorizer for  pretty  visualization of depth data
    rs2::colorizer color_map;
    //Declare RealSense pipeline, encapsulating the actual  device and  sensors
    rs2::pipeline pipe;

    rs2::config cfg;    //to configure the pipeline
    //Add desired streams to configuration
    //彩色图和深度图可以不用配置，按照默认值输出，红外图必须进行配置，否则无法显示
    cfg.enable_stream(RS2_STREAM_COLOR, RS_WIDTH, RS_HEIGHT, RS2_FORMAT_BGR8, RS_FPS);
    cfg.enable_stream(RS2_STREAM_DEPTH, RS_WIDTH, RS_HEIGHT, RS2_FORMAT_Z16, RS_FPS);
    cfg.enable_stream(RS2_STREAM_INFRARED, 1, RS_WIDTH, RS_HEIGHT, RS2_FORMAT_Y8, RS_FPS);
    cfg.enable_stream(RS2_STREAM_INFRARED, 2, RS_WIDTH, RS_HEIGHT, RS2_FORMAT_Y8, RS_FPS);

    //Start streaming with default recommended configuration
    pipe.start(cfg);

    const auto window_name = "Display Image";
    namedWindow(window_name, WINDOW_AUTOSIZE);
    char pBuf[255];     //存放路径
    getcwd(pBuf, 255);  //获取程序的当前目录
    while(getWindowProperty(window_name, WND_PROP_AUTOSIZE) >= 0)
    {
        rs2::frameset data = pipe.wait_for_frames();    //Wait for next set of frames from camera
        rs2::frame depth = data.get_depth_frame().apply_filter(color_map);  //Apply color map for visualization of depth
        rs2::frame rgb = data.get_color_frame();
        rs2::frame ir1 = data.get_infrared_frame(1);
        rs2::frame ir2 = data.get_infrared_frame(2);
        //Query frame size(width and height)
        const int depthW = depth.as<rs2::video_frame>().get_width();
        const int depthH = depth.as<rs2::video_frame>().get_height();
        const int rgbW = rgb.as<rs2::video_frame>().get_width();
        const int rgbH = rgb.as<rs2::video_frame>().get_height();

        const int irW = ir1.as<rs2::video_frame>().get_width();         //这里存疑，as是怎么用的
        const int irH = ir1.as<rs2::video_frame>().get_height();

        //Create Opencv Matrix  of size (w,h) from the colorized depth data 
        Mat depthImage(Size(depthW, depthH), CV_8UC3, (void*)depth.get_data(), Mat::AUTO_STEP);
        Mat rgbImage(Size(rgbW, rgbH), CV_8UC3, (void*)rgb.get_data(), Mat::AUTO_STEP);

        Mat ir1Image(Size(irW, irH), CV_8UC1, (void*)ir1.get_data(), Mat::AUTO_STEP);
        Mat ir2Image(Size(irW, irH), CV_8UC1, (void*)ir2.get_data(), Mat::AUTO_STEP);

        stringstream depthFile;     //depthFile.clear();    depthFile.str("");    这两步既可以清空字符串流，又可以释放内存
        stringstream rgbFile;
        stringstream ir1File;
        stringstream ir2File;
        static int image_num = 1;
        char c = (char)waitKey(1);      //if(waitKey(10) >= 0)是说10ms中按任意键进入此if块

        if(c == 27)
            std::cout << "Exit boss!" << std::endl;
        switch (c)
        {
        case 'p':
            depthFile.clear();
            depthFile.str("");
            depthFile << (string)pBuf << "/depth" << image_num << ".jpg";
            imwrite(depthFile.str(), depthImage);       //保存图片

            rgbFile.clear();
            rgbFile.str("");
            rgbFile << (string)pBuf << "/rgb" << image_num << ".jpg";
            imwrite(rgbFile.str(), rgbImage);       //保存图片

            ir1File.clear();
            ir1File.str("");
            ir1File << (string)pBuf << "/ir1-" << image_num << ".jpg";
            imwrite(ir1File.str(), ir1Image);       //保存图片
            ir2File.clear();
            ir2File.str("");
            ir2File << (string)pBuf << "/ir2-" << image_num << ".jpg";
            imwrite(ir2File.str(), ir2Image);       //保存图片

            image_num++;
            std::cout << image_num << std::endl;
            break;
        
        default:
            break;
        }

        //Update the window with new data
        imshow(window_name, depthImage);
    }
    return EXIT_SUCCESS;
}
/*catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
}*/