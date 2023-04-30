#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import rospy
import numpy as np
import h5py as h5
from std_msgs.msg import Float32MultiArray

packetSize = 512

def talker():
    pub = rospy.Publisher('packet', Float32MultiArray, queue_size=10)
    rospy.init_node('pub_packet', anonymous=True)
    rate = rospy.Rate(4)

    eegdata = np.array(h5.File('/home/sd/eegdata.mat', 'r')['eegdata']).T
    packet_pub = Float32MultiArray()
    for exper_i in range(0, eegdata.shape[3]):
        for target_i in range(0, eegdata.shape[2]):
            for packet_i in range(0, 36):
                packet = eegdata[:, packet_i * packetSize : (packet_i + 1) * packetSize, target_i, exper_i]
                packet_pub.data = packet.reshape(35 * 512)
                rospy.loginfo("I publish")
                pub.publish(packet_pub)
                rate.sleep()
		
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass