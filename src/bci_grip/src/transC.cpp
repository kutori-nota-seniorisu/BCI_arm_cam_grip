#include<iostream>
#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h" //#include "std_msgs/String.h"
#include "std_msgs/Float64.h"

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;


  vector<double> array_from_py={0,0,0,0,0,0}; 


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

void posangCallback(const std_msgs::Float64MultiArray& message_holder) 
{   
  VectorXd pose_t;
  Matrix3d pose_r;
  //ROS_INFO("received value of position: %f %f %f",message_holder.data.at(4),message_holder.data.at(5),message_holder.data.at(6));
  //ROS_INFO("euler angles: %f %f %f",message_holder.data.at(3),message_holder.data.at(4),message_holder.data.at(5)); 
  //ROS_INFO("Vector: %f %f %f",message_holder.data.at(6),message_holder.data.at(7),message_holder.data.at(8)); 
  
  array_from_py[0] = message_holder.data.at(4); 
  array_from_py[1] = message_holder.data.at(5); 
  array_from_py[2] = message_holder.data.at(6);
  array_from_py[3] = 0;
  array_from_py[4] = 0;
  array_from_py[5] = message_holder.data.at(7);
  cout<<message_holder.data.at(0); 
  //0array_from_py[6] = message_holder.data.at(6); array_from_py[7] = message_holder.data.at(7); array_from_py[8] = message_holder.data.at(8); 
  pose_t = Eigen::Map<Eigen::Matrix<double,3,1>>(&array_from_py[0],3);
  cout<<"pose_t:"<<pose_t[0]<<","<<pose_t[1]<<","<<pose_t[2]<<endl;
  Eigen::Matrix<double,3,1> tmpDatar;
  tmpDatar = Eigen::Map<Eigen::Matrix<double,3,1>>(&array_from_py[3],3);
  cout<<"pose_r:"<<tmpDatar[0]<<","<<tmpDatar[1]<<","<<tmpDatar[2]<<endl;
  Eigen::Quaterniond quaternion=rotationVector_quaternion(tmpDatar);
  pose_r=quaternion_rotationMatrix(quaternion);
  Matrix<double,4,4> End2Base;
  End2Base=rt2m(pose_t,pose_r);
  cout<<"End2Base"<<endl<<End2Base<<endl;

} 

int main(int argc, char **argv)
{
  ros::init(argc, argv, "transC");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("pos_ang", 1, posangCallback);
  ros::spin();

  return 0;
}