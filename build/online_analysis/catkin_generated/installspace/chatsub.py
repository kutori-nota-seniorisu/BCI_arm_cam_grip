#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import rospy
from std_msgs.msg import UInt16
from std_msgs.msg import Float32MultiArray

def callback_get_rate(rate):
	sampleRate = rate.data
	rospy.loginfo("I receive sample rate")
	rospy.loginfo("sample rate is : %f", sampleRate)

def callback_get_packet(data):
	rospy.loginfo("I receive packet")
	

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
	rospy.init_node('chatsub', anonymous=True)

	rospy.Subscriber("samplerate", UInt16, callback_get_rate)
	rospy.Subscriber("packet", Float32MultiArray, callback_get_packet)

	# spin() simply keeps python from exiting until this node is stopped
	rospy.spin()


if __name__ == '__main__':
	listener()
