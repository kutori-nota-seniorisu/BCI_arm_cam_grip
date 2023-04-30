#!/usr/bin/env python2
# -*- coding: UTF-8 -*-
import rospy
from std_msgs.msg import String

def callback_get_keys(msg):
    rospy.loginfo(msg.data)


def listener():
    rospy.init_node('key_control', anonymous=True)
    rospy.Subscriber('keys', String, callback_get_keys)
    rospy.spin()

if __name__ == '__main__':
    listener()