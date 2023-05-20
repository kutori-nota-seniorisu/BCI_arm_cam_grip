#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import rospy
import numpy as np
import scipy.io as scio
from std_msgs.msg import Float32MultiArray

packetSize = 512

def talker():
    pub = rospy.Publisher('packet', Float32MultiArray, queue_size=10)
    rospy.init_node('pub_packet', anonymous=True)
    rate = rospy.Rate(4)
    # rawdata =  scio.loadmat('/home/sd/eegdata_v7.mat')
    # eegdata = np.array(rawdata['eegdata'])
    rawdata =  scio.loadmat('/home/sd/matlab.mat')
    eegdata = np.array(rawdata['data'])
    eegdata = eegdata[:, 0:53248]
    eegdata = np.expand_dims(eegdata, axis = -1)
    eegdata = np.expand_dims(eegdata, axis = -1)
    eegdata = eegdata[::-1]
    print(eegdata.shape)
    packet_pub = Float32MultiArray()
    exper_i = 0
    target_i = 0
    packet_i = 0
    while not rospy.is_shutdown():
        packet = eegdata[:, packet_i * packetSize : (packet_i + 1) * packetSize, target_i, exper_i]
        packet_pub.data = packet.reshape(35 * 512)
        rospy.loginfo("I publish: %i exper, %i target, %i packet", exper_i + 1, target_i + 1, packet_i + 1)
        pub.publish(packet_pub)
        packet_i = packet_i + 1
        if packet_i % 104 == 0:
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