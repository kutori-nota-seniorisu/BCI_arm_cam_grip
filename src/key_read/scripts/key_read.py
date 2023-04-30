#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
import sys, select, tty, termios
from std_msgs.msg import String
if __name__ == '__main__':
    rospy.init_node('keyboard')
    pub = rospy.Publisher('keys', String, queue_size=1)
    rate = rospy.Rate(100)
    old_attr = termios.tcgetattr(sys.stdin)
    tty.setcbreak(sys.stdin.fileno())
    print('Please input keys, press Ctrl + c to quit')
    while not rospy.is_shutdown():
        if select.select([sys.stdin], [], [], 0)[0] == [sys.stdin]:
            pub.publish(sys.stdin.read(1))
            print(sys.stdin.read(1))
            rate.sleep()
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_attr)