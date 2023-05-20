 #include<ros/ros.h>
 #include<robotiq_2f_gripper_control/Robotiq2FGripper_robot_output.h>
 
 
 int main(int argc, char **argv)
 {
        ros::init(argc, argv, "robotiq");
        ros::NodeHandle n;
        ros::Publisher pub = n.advertise<robotiq_2f_gripper_control::Robotiq2FGripper_robot_output>("/Robotiq2FGripperRobotOutput",10);

        ros::Rate  loop_rate(1);

        int count = 0;
        while (ros::ok())
        {
            // 初始化learning_topic::Person类型的消息
    	    robotiq_2f_gripper_control::Robotiq2FGripper_robot_output Robotiq2FGripperRobotOutput;
            Robotiq2FGripperRobotOutput.rACT=1;
            Robotiq2FGripperRobotOutput.rGTO=1;
            Robotiq2FGripperRobotOutput.rATR=0;
            Robotiq2FGripperRobotOutput.rPR=0;
            Robotiq2FGripperRobotOutput. rSP=255;
            Robotiq2FGripperRobotOutput.rFR=150;

            // 发布消息
            pub.publish(Robotiq2FGripperRobotOutput);

            ROS_INFO("Publish Robotiq2FGripper_robot_output Info: rACT:%d  rGTO:%d  rATR:%d rPR:%d rSP:%d rFR:%d", 
                    Robotiq2FGripperRobotOutput.rACT,Robotiq2FGripperRobotOutput.rGTO, Robotiq2FGripperRobotOutput.rATR,Robotiq2FGripperRobotOutput.rPR,Robotiq2FGripperRobotOutput. rSP,Robotiq2FGripperRobotOutput.rFR);

            // 按照循环频率延时
            loop_rate.sleep();
    }

    return 0;

 }
