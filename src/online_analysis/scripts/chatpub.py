#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import rospy
import numpy as np
import scipy.io as scio
import h5py as h5
from std_msgs.msg import Float32MultiArray

packetSize = 512

def talker():
    pub = rospy.Publisher('packet', Float32MultiArray, queue_size=10)
    rospy.init_node('pub_packet', anonymous=True)
    rate = rospy.Rate(4)


    rawdata =  scio.loadmat('/home/sd/eegdata_v7.mat')
    eegdata = np.array(rawdata['eegdata'])
    # eegdata = np.array(h5.File('/home/sd/eegdata.mat', 'r')['eegdata']).T
    packet_pub = Float32MultiArray()
    exper_i = 0
    target_i = 0
    packet_i = 0
    while not rospy.is_shutdown():
    # for exper_i in range(0, eegdata.shape[3]):
    #     for target_i in range(0, eegdata.shape[2]):
    #         for packet_i in range(0, 36):
    #             packet = eegdata[:, packet_i * packetSize : (packet_i + 1) * packetSize, target_i, exper_i]
    #             packet_pub.data = packet.reshape(35 * 512)
    #             rospy.loginfo("I publish")
    #             pub.publish(packet_pub)
    #             rate.sleep()
        packet = eegdata[:, packet_i * packetSize : (packet_i + 1) * packetSize, target_i, exper_i]
        packet_pub.data = packet.reshape(35 * 512)
        rospy.loginfo("I publish: %i exper, %i target, %i packet", exper_i + 1, target_i + 1, packet_i + 1)
        pub.publish(packet_pub)
        packet_i = packet_i + 1
        if packet_i % 36 == 0:
            packet_i = 0
            target_i = target_i + 1
            if target_i % eegdata.shape[2] == 0:
                target_i = 0
                exper_i = exper_i + 1
                if exper_i % eegdata.shape[3] == 0:
                    rospy.loginfo("data finished")
                    break
        rate.sleep()

		
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass