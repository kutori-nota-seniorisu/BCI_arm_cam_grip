#include <opencv2/opencv.hpp>
#include <visp/vpImage.h>
#include <visp_ros/vpROSGrabber.h>
#include <iostream>
#include "ros/ros.h"
#include <visp3/core/vpConfig.h>
#include <visp3/gui/vpDisplayGDI.h>
#include <visp3/gui/vpDisplayOpenCV.h>
#include <visp3/gui/vpDisplayX.h>
#include <visp3/io/vpKeyboard.h>
#include <stdio.h>
#include <visp3/core/vpColor.h>
#include <fstream>
#include <vector>
#include <std_msgs/Int8.h>
#include "handeye.h"
#include "quaternion.h"
#include "visual_servo/toolposeChange.h"

using namespace std;
using namespace cv;


int positionSignal=-1;    //到达指定位姿后标志位改变
vector<Mat> Hgij;         //AX=XB中的B
//接收track_points发布的标志位
void handeye_signal_subCB(const std_msgs::Int8::ConstPtr &signal_sub)
{

  positionSignal=(int)signal_sub->data;
  cout << "positionSignal is " << positionSignal << endl;
}

//接收track_points发布的标志位
void pose_change_subCB(const visual_servo::toolposeChange::ConstPtr &poseChange)
{
  Mat b1(4, 4, CV_64FC1, Scalar::all(0));
  for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++)
    {
    b1.at<double>(i,j)=poseChange->pose_change[4*i+j];
  }
  }
  Hgij.push_back(b1.clone());
  cout << "poseChange is " << b1 << endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "hand_eye_calculate");
  ros::NodeHandle handle;

  //接收话题
  ros::Subscriber signal_sub=handle.subscribe("hand_eye_arm_signal", 10, handeye_signal_subCB); //订阅机械臂运动标志位
  ros::Subscriber pose_change_sub=handle.subscribe("hand_eye_arm_pose_change", 10, pose_change_subCB); //

  vpImage<unsigned char> I;  //visp用于存储捕捉到的最新图像
  Mat image;             //OpenCV存储捕捉到的最新图像
  vpROSGrabber g;

  g.setImageTopic("/camera/color/image_raw");
//  g.setImageTopic("/camera/color/image_raw");
  g.open(I);          //打开相机
  g.acquire(I);       //获取图像
  vpImageConvert::convert(I, image);   //图像类型转换
  //参数变量
    const int image_count = 7;	               //需要保存的图片数量
    int count = 0;  //计算保存的标定图像数量
    int n = 0;        //保存图片的名称
    stringstream tempname;
    string filename;
    Size image_size = image.size();     //图像的尺寸
    Size board_size = Size(11, 8);            /****    定标板上每行、列的角点数       ****/

    vector<Point2f> corners;                  /****    缓存每幅图像上检测到的角点       ****/
    string msg;
    int baseLine;
    Size textSize;
    int key;         //记录按键值

    //solvePnP参数
    vector<Point3f> objP;
    objP.push_back(Point3f(0,0,0));
    objP.push_back(Point3f(0,100,0));
    objP.push_back(Point3f(0,200,0));
    objP.push_back(Point3f(140,0,0));
    objP.push_back(Point3f(140,100,0));
    objP.push_back(Point3f(140,200,0));



    Mat objPM;
    Mat(objP).convertTo(objPM,CV_32F);
    //相机参数
//    Focal Length:          fc = [ 1586.00282   1585.83712 ] +/- [ 4.58810   4.60385 ]
//    Principal point:       cc = [ 638.32901   510.73652 ] +/- [ 2.62558   2.10881 ]
//    Skew:             alpha_c = [ 0.00000 ] +/- [ 0.00000  ]   => angle of pixel axes = 90.00000 +/- 0.00000 degrees
//    Distortion:            kc = [ -0.06359   0.03602   -0.00002   -0.00003  0.00000 ] +/- [ 0.00702   0.05941   0.00037   0.00046  0.00000 ]
//    Pixel error:          err = [ 0.17678   0.21819 ]

////realsense internal parameters read directly
//D: [0.14534789323806763, -0.4564165472984314, -0.0010384570341557264, -0.0005411147139966488, 0.43104979395866394]
//K: [899.0191650390625, 0.0, 656.3931274414062, 0.0, 899.7249145507812, 356.31396484375, 0.0, 0.0, 1.0]

////realsense internal parameters obtained by Zhang Zhengyou calibration method
// Focal Length:          fc = [ 894.20742   895.31735 ] +/- [ 1.66562   1.65416 ]
// Principal point:       cc = [ 652.92485   361.94194 ] +/- [ 1.00506   0.78743 ]
// Skew:             alpha_c = [ 0.00000 ] +/- [ 0.00000  ]   => angle of pixel axes = 90.00000 +/- 0.00000 degrees
// Distortion:            kc = [ 0.09765   -0.20064   0.00183   -0.00082  0.00000 ] +/- [ 0.00243   0.00685   0.00030   0.00039  0.00000 ]
// Pixel error:          err = [ 0.10814   0.09645 ]

    double camD[9] = {901.01109, 0, 653.47684 ,
    0, 901.77156 , 359.66719,
    0, 0, 1};

    double distCoeffD[5] = { 0.11777   ,-0.26212   ,0.00130   ,-0.00132  ,0.00000};
    Mat camera_matrix = Mat(3,3,CV_64FC1,camD);
    Mat distortion_coefficients = Mat(5,1,CV_64FC1,distCoeffD);

    //计算手眼关系参数
    vector<Mat> v_rotM;
    vector<Mat> v_tvec;

    cv::namedWindow("camera exterior calibration", cv::WINDOW_AUTOSIZE);
    while (n < image_count && ros::ok())
    {
      g.acquire(I);       //获取图像
      vpImageConvert::convert(I, image);   //图像类型转换
      if (image.empty())
      {
        cout << "img is empty" << endl;
        g.close();
        return -1;
      }

      //Mat imageGray = image;
      //cvtColor(image, imageGray, CV_RGB2GRAY);	//彩色图片需要转化为灰度图

      // 提取角点
      bool patternfound = findChessboardCorners(image, board_size, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);

      key = 0xff & waitKey(50);
      ros::spinOnce();

      if ((key & 255) == 32  || positionSignal!=-1)   //  空格键
      {
        positionSignal=-1;   //重新赋值，为下一个位姿做准备
        if (patternfound)
        {
          n++;
          tempname << "result/" << n;
          tempname >> filename;
          filename += ".jpg";
          /* 亚像素精确化 */
          cornerSubPix(image, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
          count += corners.size();
          imwrite(filename, image);
          tempname.clear();
          filename.clear();

          vector<Point2f> imgP;
          imgP.push_back(corners.at(0));
          imgP.push_back(corners.at(5));
          imgP.push_back(corners.at(10));
          imgP.push_back(corners.at(77));
          imgP.push_back(corners.at(82));
          imgP.push_back(corners.at(87));


          //solvePnP求解相机坐标系下目标物的位姿
          vector<double> rv(3), tv(3);
          Mat rvec(rv), tvec(tv);
          double rm[9];
          Mat rotM(3,3,CV_64FC1,rm);

          Rodrigues(rotM,rvec);
          solvePnP(objPM, Mat(imgP), camera_matrix, distortion_coefficients, rvec, tvec);
          Rodrigues(rvec,rotM);

          v_rotM.push_back(rotM.clone());
          v_tvec.push_back(tvec.clone());
          cout<<"图片数量：  "<<n<<endl;
          cout<<"rotation matrix: "<<endl<<rotM<<endl;
              //cout<<"translation matrix: "<<endl<<tv[0]<<" "<<tv[1]<<" "<<tv[2]<<endl;
          cout<<"tvec matrix: "<<endl<<tvec.at<double>(0,0)<<" "<<tvec.at<double>(1,0)<<" "<<tvec.at<double>(2,0)<<endl;
        }
        else
        {
          std::cout << "Detect Failed.\n";
        }
      }
      else if ((key & 255) == 27)     //按esc键退出
      {
        break;
      }

      for(int i=0;i<corners.size();i++)
      {
        cv::circle(image,corners.at(i),8,CV_RGB(255,0,255),2);
      }

      baseLine = 0;
      textSize = getTextSize(msg, 1, 1, 1, &baseLine);
      Point textOrigin(image.cols - 2 * textSize.width - 10, image.rows - 2 * baseLine - 10);
      msg = format("Press 'esc' to quit  %d/%d", n, image_count);
      putText(image, msg, textOrigin, 1, 1, CV_RGB(0, 0, 255));
      cv::imshow("camera exterior calibration", image);
    }
    g.close();

    if(n==image_count)  //达到计数要求，开始标定手眼关系
    {
      ofstream hand_eye_fout("result/hand_eye_result.txt");  /**    保存标定结果的文件     **/
      vector<Mat> Hcij;

      for(int i=1;i<image_count;i++)
      {
        Mat a1(4, 4, CV_64FC1, Scalar::all(0));
        Mat a_r=Mat(3,3,CV_64FC1,Scalar::all(0));
        Mat a_t=Mat(3,1,CV_64FC1,Scalar::all(0));
        a_r=v_rotM.at(i-1)*v_rotM.at(i).t();
        a_t=v_rotM.at(i-1)*(-v_rotM.at(i).t()*v_tvec.at(i))+v_tvec.at(i-1);

        for(int j=0; j<3; j++)
        {
          for(int k=0; k<3; k++)
          {
            a1.at<double>(j,k)=a_r.at<double>(j,k);
          }
        }
        for(int j=0; j<3; j++)
        {
          a1.at<double>(j,3)=a_t.at<double>(j,0)/1000;
        }
        a1.at<double>(3,3)=1.0;

        Hcij.push_back(a1.clone());
      }

      for(int i=0;i<Hcij.size();i++)
      {
        cout<<"Hcij "<< i << endl <<Hcij.at(i)<<endl;
      }
      for(int i=0;i<Hgij.size();i++)
      {
        cout<<"Hgij "<< i << endl <<Hgij.at(i)<<endl;
      }

      cout<<"Hcij"<<Hcij.size()<<endl;
      cout<<"Hgij"<<Hgij.size()<<endl;

      Mat Hcg1(4, 4, CV_64FC1);
      Tsai_HandEye(Hcg1, Hgij, Hcij);
      cout<<"Hcg1:"<<Hcg1<<endl;

      Mat Hcg2(4, 4, CV_64FC1);
      DualQ_HandEye(Hcg2, Hgij, Hcij);
      cout<<"Hcg2:"<<Hcg2<<endl;

      Mat Hcg3(4, 4, CV_64FC1);
      Inria_HandEye(Hcg3, Hgij, Hcij);
      cout<<"Hcg3:"<<Hcg3<<endl;

      Mat Hcg4(4, 4, CV_64FC1);
      Navy_HandEye(Hcg4, Hgij, Hcij);
      cout<<"Hcg4:"<<Hcg4<<endl;

      Mat Hcg5(4, 4, CV_64FC1);
      Kron_HandEye(Hcg5, Hgij, Hcij);
      cout<<"Hcg5:"<<Hcg5<<endl;
      hand_eye_fout << "相机坐标系到手爪坐标系的转换关系" << endl;
      hand_eye_fout << "Tsai_HandEye;" << endl;
      hand_eye_fout << Hcg1 << endl << endl;
      hand_eye_fout << "DualQ_HandEye;" << endl;
      hand_eye_fout << Hcg2 << endl << endl;
      hand_eye_fout << "Inria_HandEye;" << endl;
      hand_eye_fout << Hcg3 << endl << endl;
      hand_eye_fout << "Navy_HandEye;" << endl;
      hand_eye_fout << Hcg4 << endl << endl;
      hand_eye_fout << "Kron_HandEye;" << endl;
      hand_eye_fout << Hcg5 << endl << endl << endl;

    }

    cout << "手眼标定完成" << endl;
    return 0;

}




