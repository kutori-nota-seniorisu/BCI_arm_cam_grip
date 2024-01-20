#include <string>
#include <ros/ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Bool.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
Eigen::MatrixXd Point3D;
int main(int argc, char** argv) {
    ros::init(argc, argv, "testeigen");
    ros::NodeHandle n;
    vector<double> ttt = {1, 2, 3};
    Point3D = Eigen::Map<Eigen::MatrixXd> (&ttt[0], 2, 3);
    // Point3D(0, 0) = 3;
    // Point3D(0, 1) = 3;
    // Point3D(0, 2) = 3;
    // Point3D(2, 1) = 3;
    // Point3D(2, 2) = 3;
    while(ros::ok())
        cout << Point3D(0,3) << endl;
        // cout << "1" << endl;
    return 0;
}