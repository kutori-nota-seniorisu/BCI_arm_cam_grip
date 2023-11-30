#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Int8.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <ur_rtde/rtde_control_interface.h>

#include <ur_rtde/rtde.h>
#include <ur_rtde/rtde_receive_interface_doc.h>
#include <ur_rtde/robot_state.h>
#include <ur_rtde/rtde_export.h>
#include <ur_rtde/rtde_utility.h>
#include <ur_rtde/rtde_io_interface.h>

#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <Eigen/Core>

#include "visual_servo/toolposeChange.h"

const float deg2rad = M_PI / 180.0;//用于将角度转化为弧度。rad = deg*deg2rad
const float rad2deg = 180.0 / M_PI;//用于将弧度转化为角度。deg = rad*rad2deg


# define INITPOSE {-0.0494694,-0.546101,0.177864,-0.243984,-2.94866,-0.0205401}
# define POSE1 {-0.207282,-0.516908,0.141509,-0.12847,2.9609,-0.0380256}
# define POSE2 {-0.176869,-0.394898,0.0925324, -0.140634,3.02963,-0.652424}
# define POSE3 {-0.257702,-0.371825,0.120631, -0.332779,2.68568,-0.593299}
# define POSE4 {-0.0127899,-0.449775,0.0701355, 0.155459,-2.68906,0.34621}
# define POSE5 {-0.0683925,-0.639404,0.108638, 0.455588,-2.84449,-0.650023}
# define POSE6 {-0.113948,-0.53579,0.139568, 0.113606,-3.13022,-0.0234544}

# define USE_UR_SIM 0
typedef struct
{
  Eigen::Matrix<double,6,1> pose;
  Eigen::Matrix<double,6,1> speed;
  Eigen::Matrix<double,6,1> accel;
  Eigen::Matrix<double,6,1> force;
}Admittance_Status_Cart;


using namespace ur_rtde;
using namespace std;
using namespace Eigen;
double speed=0.5;
double acceleration=0.5;

#if USE_UR_SIM
RTDEControlInterface rtde_control("127.0.0.1");
//ur_rtde::RTDEReceiveInterface rtde_receive("127.0.0.1");
#else
RTDEControlInterface rtde_control("192.168.0.104");
ur_rtde::RTDEReceiveInterface rtde_receive("192.168.0.104");
#endif

//旋转矢量到四元数
Eigen::Quaterniond rotationVector_quaternion(Eigen::Matrix<double,3,1> rotationVector)
{
  Eigen::Quaterniond quaternion;
  double theat = rotationVector.norm();
  quaternion.w() = cos(theat / 2);
  if(abs(theat) < 0.0001){
    theat += theat > 0 ? 0.0001 : -0.0001;
  }
  quaternion.x() = rotationVector[0] / theat * sin(theat / 2);
  quaternion.y() = rotationVector[1] / theat * sin(theat / 2);
  quaternion.z() = rotationVector[2] / theat * sin(theat / 2);
  return quaternion;
}

//四元数转换为旋转矩阵
Eigen::Matrix3d quaternion_rotationMatrix(Eigen::Quaterniond quaternion)
{
  return quaternion.toRotationMatrix();
}
//获取基座标系base下末端坐标系tool0的位置pose_t和姿态pose_r（旋转矩阵）
int getPose(const tf2_ros::Buffer &tfBuffer_,VectorXd &pose_t,Matrix3d &pose_r)
{
    std::vector<double> nowUrPose;
    nowUrPose = rtde_receive.getActualTCPPose();
    pose_t = Eigen::Map<Eigen::Matrix<double,3,1>>(&nowUrPose[0],3);
    Eigen::Matrix<double,3,1> tmpDatar;
    tmpDatar = Eigen::Map<Eigen::Matrix<double,3,1>>(&nowUrPose[3],3);
    Eigen::Quaterniond quaternion=rotationVector_quaternion(tmpDatar);
    pose_r=quaternion_rotationMatrix(quaternion);
    Eigen::Matrix<double,3,1> tmpDatar1;
    cout<<"pose_r"<<pose_r<<endl;


   //joint
    std::vector<double> nowUrjoint;
    nowUrjoint = rtde_receive.getActualQ();
    VectorXd joint;
    joint = Eigen::Map<Eigen::Matrix<double,6,1>>(&nowUrjoint[0],6);
    cout<<"joint:"<<joint<<endl;
    return 0;
}
//旋转矩阵转换为欧拉ZYX/RPY
//ZYX顺序，即先绕x轴roll,再绕y轴pitch,最后绕z轴yaw,0表示X轴,1表示Y轴,2表示Z轴
Eigen::Vector3d  rotationMatrix_RPY(Eigen::Matrix3d rotationMatrix){
  return rotationMatrix.eulerAngles(2, 1, 0);
}

//获取old位姿坐标系下，从old到new的位置和姿态增量
MatrixXd getPoseIncreasement(VectorXd poseNew_t,Matrix3d &poseNew_r,VectorXd poseOld_t,Matrix3d &poseOld_r)
{

  Matrix3d R_old_new;
  VectorXd t_old_new(3);
  R_old_new = poseOld_r.transpose()*poseNew_r;
  t_old_new = poseOld_r.transpose()*poseNew_t-poseOld_r.transpose()*poseOld_t;

  MatrixXd old_new = MatrixXd::Zero(4, 4);
  for(int j=0; j<3; j++)
  {
    for(int k=0; k<3; k++)
  {
    old_new(j,k)=R_old_new(j,k);
  }
  }
  for(int j=0; j<3; j++)
  {
    old_new(j,3)=t_old_new(j);
  }
  old_new(3,3)=1.0;

 // cout<<"d_pose"<<endl<<d_pose_<<endl;

  return old_new;
}
Eigen::Vector3d  rotationMatrix_euler(Eigen::Matrix3d rotationMatrix){
  return rotationMatrix.eulerAngles(2, 1, 0);
}
//旋转矩阵和平移向量转齐次矩阵
MatrixXd rt2m(const VectorXd pose_t,const Matrix3d pose_r)
{
  MatrixXd pose_m = MatrixXd::Zero(4, 4);
  for(int j=0; j<3; j++)
    {
      for(int k=0; k<3; k++)
    {
      pose_m(j,k)=pose_r(j,k);
    }
    }
  for(int j=0; j<3; j++)
  {
      pose_m(j,3)=pose_t(j);
  }
  pose_m(3,3)=1.0;

  return pose_m;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "hand_eye_arm_control");   //定义节点名称
    ros::NodeHandle handle;   //为这个进程的节点创建一个句柄
    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);  //获取机械臂末端在基坐标系下的位姿
    //发布的消息
    ros::Publisher signal_pub = handle.advertise<std_msgs::Int8>("/hand_eye_arm_signal", 1);  //到达位姿后，发送标志位
    ros::Publisher pose_change_pub = handle.advertise<visual_servo::toolposeChange>("hand_eye_arm_pose_change", 10);//发送末端位姿齐次变换矩阵
    ros::Publisher pose_pub = handle.advertise<visual_servo::toolposeChange>("hand_eye_arm_pose", 10);//发送末端位姿齐次变换矩阵

    Admittance_Status_Cart ctrlStatus;

    Matrix3d poseNew_r = MatrixXd::Zero(3, 3);						//本周期获取的姿态
    VectorXd poseNew_t = MatrixXd::Zero(3, 1);						//理想位置
    Matrix3d poseOld_r = MatrixXd::Zero(3, 3);						//本周期获取的姿态
    VectorXd poseOld_t = MatrixXd::Zero(3, 1);						//理想位置
    MatrixXd d_pose = MatrixXd::Zero(4, 4);						//用于某一次存放位姿变化增量的向量

    std_msgs::Int8 flag;	//到达位姿后，发送标志位
    visual_servo::toolposeChange poseChange;   //末端位姿齐次变换矩阵
    MatrixXd pose_m=MatrixXd::Zero(4, 4);   //基坐标系下末端位姿
    visual_servo::toolposeChange pose;   //基坐标系下末端位姿
    flag.data=1;


    std::vector<double> nowUrPose;
    VectorXd pose_t;
    Matrix3d pose_r;
    nowUrPose = rtde_receive.getActualTCPPose();
    pose_t = Eigen::Map<Eigen::Matrix<double,3,1>>(&nowUrPose[0],3);
    cout<<"pose_t:"<<pose_t[0]<<","<<pose_t[1]<<","<<pose_t[2]<<endl;
    Eigen::Matrix<double,3,1> tmpDatar;
    tmpDatar = Eigen::Map<Eigen::Matrix<double,3,1>>(&nowUrPose[3],3);
    cout<<"pose_r:"<<tmpDatar[0]<<","<<tmpDatar[1]<<","<<tmpDatar[2]<<endl;
    Eigen::Quaterniond quaternion=rotationVector_quaternion(tmpDatar);
    pose_r=quaternion_rotationMatrix(quaternion);
    Matrix<double,4,4> End2Base;
    End2Base=rt2m(pose_t,pose_r);
    cout<<"End2Base"<<endl<<End2Base<<endl;
    Eigen::Vector3d euler=rotationMatrix_euler(pose_r);
    cout<<"euler"<<endl<<euler<<endl;
    //joint
     std::vector<double> nowUrjoint;
     nowUrjoint = rtde_receive.getActualQ();
     VectorXd joint;
     joint = Eigen::Map<Eigen::Matrix<double,6,1>>(&nowUrjoint[0],6);
     cout<<"joint:"<<joint<<endl;

//     nowUrjoint.clear();
//     nowUrjoint={-1.5707963,-1.5707963,-1.5707963,-1.5707963,1.5707963,0};
//     rtde_control.servoJ(nowUrjoint,speed,acceleration,0.5,0.03,600);
      /**************************************************************************************************************************/
      /****************************************************1. 初始位姿***************************************************/
      /**************************************************************************************************************************/
    cout<<"位姿1 拍摄第1张照片"<<endl;
    std::vector<double> initpose1 = INITPOSE;
    ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&initpose1[0], 6, 1);
    ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
    rtde_control.servoL(initpose1, speed, acceleration, 1,  0.03, 600);
    sleep(4);
    getPose(tfBuffer,poseNew_t,poseNew_r);
    cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
    cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
    poseOld_t=poseNew_t;
    poseOld_r=poseNew_r;
    //发送标志位
    signal_pub.publish(flag);
    ros::Duration(2).sleep();
    flag.data=2;

////    /**************************************************************************************************************************/
////    /****************************************************2. 位姿1***************************************************/
////    /**************************************************************************************************************************/
   cout<<"位姿2 拍摄第2张照片"<<endl;
   std::vector<double> Pose1 = POSE1;
   ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose1[0], 6, 1);
   ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
   rtde_control.servoL(Pose1, speed, acceleration, 1,  0.03, 600);
   sleep(4);
   getPose(tfBuffer,poseNew_t,poseNew_r);


   d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
   cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
   cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
   cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
   cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
   cout<<"d_pose"<<endl<<d_pose<<endl;
   poseOld_t=poseNew_t;
   poseOld_r=poseNew_r;

     //当前末端位姿
     pose_m=rt2m(poseNew_t,poseNew_r);
     //发送运动前到运动后末端位姿的变换矩阵
     for(int i=0; i<4; i++)
       {
         for(int j=0; j<4; j++)
       {
         poseChange.pose_change[4*i+j]=d_pose(i,j);
       pose.pose_change[4*i+j]=pose_m(i,j);
       }
       }
     pose_change_pub.publish(poseChange);
     pose_pub.publish(pose);
     //发送标志位
     signal_pub.publish(flag);
     ros::Duration(2).sleep();
     flag.data=3;


//      /**************************************************************************************************************************/
//      /****************************************************2. 位姿1***************************************************/
//      /**************************************************************************************************************************/
     cout<<"位姿3 拍摄第3张照片"<<endl;
     std::vector<double> Pose2 = POSE2;
     ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose2[0], 6, 1);
     ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
     rtde_control.servoL(Pose2, speed, acceleration, 1,  0.03, 600);
     sleep(4);
     getPose(tfBuffer,poseNew_t,poseNew_r);


     d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
     cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
     cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
     cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
     cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
     cout<<"d_pose"<<endl<<d_pose<<endl;
     poseOld_t=poseNew_t;
     poseOld_r=poseNew_r;

       //当前末端位姿
       pose_m=rt2m(poseNew_t,poseNew_r);
       //发送运动前到运动后末端位姿的变换矩阵
       for(int i=0; i<4; i++)
         {
           for(int j=0; j<4; j++)
         {
           poseChange.pose_change[4*i+j]=d_pose(i,j);
         pose.pose_change[4*i+j]=pose_m(i,j);
         }
         }
       pose_change_pub.publish(poseChange);
       pose_pub.publish(pose);
       //发送标志位
       signal_pub.publish(flag);
       ros::Duration(2).sleep();
       flag.data=4;
//        /**************************************************************************************************************************/
//        /****************************************************2. 位姿1***************************************************/
//        /**************************************************************************************************************************/
       cout<<"位姿4 拍摄第4张照片"<<endl;
       std::vector<double> Pose3 = POSE3;
       ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose3[0], 6, 1);
       ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
       rtde_control.servoL(Pose3, speed, acceleration, 1,  0.03, 600);
       sleep(4);
       getPose(tfBuffer,poseNew_t,poseNew_r);


       d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
       cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
       cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
       cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
       cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
       cout<<"d_pose"<<endl<<d_pose<<endl;
       poseOld_t=poseNew_t;
       poseOld_r=poseNew_r;

         //当前末端位姿
         pose_m=rt2m(poseNew_t,poseNew_r);
         //发送运动前到运动后末端位姿的变换矩阵
         for(int i=0; i<4; i++)
           {
             for(int j=0; j<4; j++)
           {
             poseChange.pose_change[4*i+j]=d_pose(i,j);
           pose.pose_change[4*i+j]=pose_m(i,j);
           }
           }
         pose_change_pub.publish(poseChange);
         pose_pub.publish(pose);
         //发送标志位
         signal_pub.publish(flag);
         ros::Duration(2).sleep();
         flag.data=5;
//          /**************************************************************************************************************************/
//          /****************************************************2. 位姿1***************************************************/
//          /**************************************************************************************************************************/
         cout<<"位姿5 拍摄第5张照片"<<endl;
         std::vector<double> Pose4 = POSE4;
         ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose4[0], 6, 1);
         ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
         rtde_control.servoL(Pose4, speed, acceleration, 1,  0.03, 600);
         sleep(4);
         getPose(tfBuffer,poseNew_t,poseNew_r);


         d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
         cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
         cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
         cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
         cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
         cout<<"d_pose"<<endl<<d_pose<<endl;
         poseOld_t=poseNew_t;
         poseOld_r=poseNew_r;

           //当前末端位姿
           pose_m=rt2m(poseNew_t,poseNew_r);
           //发送运动前到运动后末端位姿的变换矩阵
           for(int i=0; i<4; i++)
             {
               for(int j=0; j<4; j++)
             {
               poseChange.pose_change[4*i+j]=d_pose(i,j);
             pose.pose_change[4*i+j]=pose_m(i,j);
             }
             }
           pose_change_pub.publish(poseChange);
           pose_pub.publish(pose);
           //发送标志位
           signal_pub.publish(flag);
           ros::Duration(2).sleep();
           flag.data=6;


           cout<<"位姿6 拍摄第6张照片"<<endl;
           std::vector<double> Pose5 = POSE5;
           ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose5[0], 6, 1);
           ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
           rtde_control.servoL(Pose5, speed, acceleration, 1,  0.03, 600);
           sleep(4);
           getPose(tfBuffer,poseNew_t,poseNew_r);


           d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
           cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
           cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
           cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
           cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
           cout<<"d_pose"<<endl<<d_pose<<endl;
           poseOld_t=poseNew_t;
           poseOld_r=poseNew_r;

             //当前末端位姿
             pose_m=rt2m(poseNew_t,poseNew_r);
             //发送运动前到运动后末端位姿的变换矩阵
             for(int i=0; i<4; i++)
               {
                 for(int j=0; j<4; j++)
               {
                 poseChange.pose_change[4*i+j]=d_pose(i,j);
               pose.pose_change[4*i+j]=pose_m(i,j);
               }
               }
             pose_change_pub.publish(poseChange);
             pose_pub.publish(pose);
             //发送标志位
             signal_pub.publish(flag);
             ros::Duration(2).sleep();
             flag.data=7;

             cout<<"位姿7 拍摄第7张照片"<<endl;
             std::vector<double> Pose6 = POSE6;
             ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose6[0], 6, 1);
             ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
             rtde_control.servoL(Pose6, speed, acceleration, 1,  0.03, 600);
             sleep(4);
             getPose(tfBuffer,poseNew_t,poseNew_r);


             d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
             cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
             cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
             cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
             cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
             cout<<"d_pose"<<endl<<d_pose<<endl;
             poseOld_t=poseNew_t;
             poseOld_r=poseNew_r;

               //当前末端位姿
               pose_m=rt2m(poseNew_t,poseNew_r);
               //发送运动前到运动后末端位姿的变换矩阵
               for(int i=0; i<4; i++)
                 {
                   for(int j=0; j<4; j++)
                 {
                   poseChange.pose_change[4*i+j]=d_pose(i,j);
                 pose.pose_change[4*i+j]=pose_m(i,j);
                 }
                 }
               pose_change_pub.publish(poseChange);
               pose_pub.publish(pose);
               //发送标志位
               signal_pub.publish(flag);
               ros::Duration(2).sleep();
               flag.data=8;
























//                cout<<"位姿8 拍摄第8张照片"<<endl;
//                std::vector<double> Pose7 = POSE7;
//                ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose7[0], 6, 1);
//                ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
//                rtde_control.servoL(Pose7, speed, acceleration, 1,  0.03, 600);
//                sleep(4);
//                getPose(tfBuffer,poseNew_t,poseNew_r);


//                d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
//                cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
//                cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
//                cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
//                cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
//                cout<<"d_pose"<<endl<<d_pose<<endl;
//                poseOld_t=poseNew_t;
//                poseOld_r=poseNew_r;

//                  //当前末端位姿
//                  pose_m=rt2m(poseNew_t,poseNew_r);
//                  //发送运动前到运动后末端位姿的变换矩阵
//                  for(int i=0; i<4; i++)
//                    {
//                      for(int j=0; j<4; j++)
//                    {
//                      poseChange.pose_change[4*i+j]=d_pose(i,j);
//                    pose.pose_change[4*i+j]=pose_m(i,j);
//                    }
//                    }
//                  pose_change_pub.publish(poseChange);
//                  pose_pub.publish(pose);
//                  //发送标志位
//                  signal_pub.publish(flag);
//                  ros::Duration(2).sleep();
//                  flag.data=9;

//                  cout<<"位姿9 拍摄第9张照片"<<endl;
//                  std::vector<double> Pose8 = POSE8;
//                  ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose8[0], 6, 1);
//                  ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
//                  rtde_control.servoL(Pose8, speed, acceleration, 1,  0.03, 600);
//                  sleep(4);
//                  getPose(tfBuffer,poseNew_t,poseNew_r);


//                  d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
//                  cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
//                  cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
//                  cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
//                  cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
//                  cout<<"d_pose"<<endl<<d_pose<<endl;
//                  poseOld_t=poseNew_t;
//                  poseOld_r=poseNew_r;

//                    //当前末端位姿
//                    pose_m=rt2m(poseNew_t,poseNew_r);
//                    //发送运动前到运动后末端位姿的变换矩阵
//                    for(int i=0; i<4; i++)
//                      {
//                        for(int j=0; j<4; j++)
//                      {
//                        poseChange.pose_change[4*i+j]=d_pose(i,j);
//                      pose.pose_change[4*i+j]=pose_m(i,j);
//                      }
//                      }
//                    pose_change_pub.publish(poseChange);
//                    pose_pub.publish(pose);
//                    //发送标志位
//                    signal_pub.publish(flag);
//                    ros::Duration(2).sleep();
//                    flag.data=10;


////                cout<<"位姿2 拍摄第3张照片"<<endl;
////                std::vector<double> Pose7 = POSE7;
////                ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose7[0], 6, 1);
////                ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
////                rtde_control.servoL(Pose7, speed, acceleration, 1,  0.03, 600);
////                sleep(4);
////                getPose(tfBuffer,poseNew_t,poseNew_r);


////                d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
////                cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
////                cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
////                cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
////                cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
////                cout<<"d_pose"<<endl<<d_pose<<endl;
////                poseOld_t=poseNew_t;
////                poseOld_r=poseNew_r;

////                  //当前末端位姿
////                  pose_m=rt2m(poseNew_t,poseNew_r);
////                  //发送运动前到运动后末端位姿的变换矩阵
////                  for(int i=0; i<4; i++)
////                    {
////                      for(int j=0; j<4; j++)
////                    {
////                      poseChange.pose_change[4*i+j]=d_pose(i,j);
////                    pose.pose_change[4*i+j]=pose_m(i,j);
////                    }
////                    }
////                  pose_change_pub.publish(poseChange);
////                  pose_pub.publish(pose);
////                  //发送标志位
////                  signal_pub.publish(flag);
////                  ros::Duration(2).sleep();
////                  flag.data=9;
////                  cout<<"位姿2 拍摄第3张照片"<<endl;
////                  std::vector<double> Pose8 = POSE8;
////                  ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose8[0], 6, 1);
////                  ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
////                  rtde_control.servoL(Pose8, speed, acceleration, 1,  0.03, 600);
////                  sleep(4);
////                  getPose(tfBuffer,poseNew_t,poseNew_r);


////                  d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
////                  cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
////                  cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
////                  cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
////                  cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
////                  cout<<"d_pose"<<endl<<d_pose<<endl;
////                  poseOld_t=poseNew_t;
////                  poseOld_r=poseNew_r;

////                    //当前末端位姿
////                    pose_m=rt2m(poseNew_t,poseNew_r);
////                    //发送运动前到运动后末端位姿的变换矩阵
////                    for(int i=0; i<4; i++)
////                      {
////                        for(int j=0; j<4; j++)
////                      {
////                        poseChange.pose_change[4*i+j]=d_pose(i,j);
////                      pose.pose_change[4*i+j]=pose_m(i,j);
////                      }
////                      }
////                    pose_change_pub.publish(poseChange);
////                    pose_pub.publish(pose);
////                    //发送标志位
////                    signal_pub.publish(flag);
////                    ros::Duration(2).sleep();
////                    flag.data=10;
////                    cout<<"位姿2 拍摄第3张照片"<<endl;
////                    std::vector<double> Pose9 = POSE9;
////                    ctrlStatus.pose << Eigen::Map<Eigen::MatrixXd>(&Pose9[0], 6, 1);
////                    ctrlStatus.speed << 0.0,0.0,0.0,0.0,0.0,0.0;
////                    rtde_control.servoL(Pose4, speed, acceleration, 1,  0.03, 600);
////                    sleep(4);
////                    getPose(tfBuffer,poseNew_t,poseNew_r);


////                    d_pose=getPoseIncreasement(poseNew_t,poseNew_r,poseOld_t,poseOld_r);
////                    cout<<"poseNew_r"<<endl<<poseNew_r<<endl;
////                    cout<<"poseNew_t"<<endl<<poseNew_t<<endl;
////                    cout<<"poseOld_t"<<endl<<poseOld_t<<endl;
////                    cout<<"poseOld_r"<<endl<<poseOld_r<<endl;
////                    cout<<"d_pose"<<endl<<d_pose<<endl;
////                    poseOld_t=poseNew_t;
////                    poseOld_r=poseNew_r;

////                      //当前末端位姿
////                      pose_m=rt2m(poseNew_t,poseNew_r);
////                      //发送运动前到运动后末端位姿的变换矩阵
////                      for(int i=0; i<4; i++)
////                        {
////                          for(int j=0; j<4; j++)
////                        {
////                          poseChange.pose_change[4*i+j]=d_pose(i,j);
////                        pose.pose_change[4*i+j]=pose_m(i,j);
////                        }
////                        }
////                      pose_change_pub.publish(poseChange);
////                      pose_pub.publish(pose);
////                      //发送标志位
////                      signal_pub.publish(flag);
////                      ros::Duration(2).sleep();
////                      flag.data=11;

  }

