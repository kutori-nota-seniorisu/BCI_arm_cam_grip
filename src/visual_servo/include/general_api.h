#ifndef GENERAL_API_H
#define GENERAL_API_H
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/WrenchStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <tf2_ros/transform_listener.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Int8.h>
#include <unistd.h>   // for function usleep(microseconds)
#include <cstdlib>
#include <ur_rtde/rtde_receive_interface.h>// rtde
#include <ur_rtde/rtde_control_interface.h>
#include <thread>
#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
#include "visual_control/circle.h"
using namespace ur_rtde;
using namespace std;
using namespace Eigen;
using namespace cv;
//旋转矩阵转换为欧拉角
//ZYX顺序，即先绕x轴roll,再绕y轴pitch,最后绕z轴yaw,0表示X轴,1表示Y轴,2表示Z轴
Eigen::Vector3d  rotationMatrix_euler(Eigen::Matrix3d rotationMatrix);
//欧拉角转换为四元数
Eigen::Quaterniond euler_quaternion(Eigen::Vector3d eulerAngle);
//四元数转换为旋转矢量
Eigen::Matrix<double,3,1> quaternion_rotationVector(Eigen::Quaterniond quaternion);
//旋转矢量到四元数
Eigen::Quaterniond rotationVector_quaternion(Eigen::Matrix<double,3,1> rotationVector);
//四元数转换为旋转矩阵
Eigen::Matrix3d quaternion_rotationMatrix(Eigen::Quaterniond quaternion);
//旋转矩阵和平移向量转齐次矩阵
MatrixXd rt2m(const VectorXd pose_t,const Matrix3d pose_r);
/*函数功能：求两条直线交点*/
Point2f getCrossPoint(Vec4d LineA, Vec4d LineB);
/*函数功能：求两条直线JIAJIAO*/
double getAngle(Vec4d LineA, Vec4d LineB);

#endif // GENERAL_API_H
