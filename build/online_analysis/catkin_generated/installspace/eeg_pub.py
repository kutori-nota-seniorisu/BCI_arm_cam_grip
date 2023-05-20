#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import rospy
import numpy as np
import matplotlib.pyplot as plt
import scipy.io as scio
from std_msgs.msg import String
from std_msgs.msg import Float32MultiArray

# 每个数据包大小
packetSize = 512

# 读取脑电数据
print("I read start")
rawdata =  scio.loadmat('/home/sd/eegdata_del3s_dim2cat_v7.mat')
eegdata = np.array(rawdata['eegdata']) # 35x122880x9
print("I read finish")

# 生成19Hz噪声信号
# t = np.array([(i * 1.0) / 2048 for i in range(0, 122880)])
# sin30ref = np.sin(2 * np.pi * 19 * t)
# sin30ref = np.tile(sin30ref, (35, 1))

# 生成高斯噪声
# gauss_noise = np.random.normal(0, 1, (35, 122880))

# 记录按键输入
target = 0
# 记录数据包个数
packet_i = 0

def talker():
    global packet_i

    # 定义发布对象
    pub = rospy.Publisher('packet', Float32MultiArray, queue_size=10)
    # 设置发布频率
    rate = rospy.Rate(4)
    # 定义被发送的话题变量
    packet_pub = Float32MultiArray()
    while not rospy.is_shutdown():
        if target == 0:
            # if (packet_i + 1) * packetSize >= eegdata.shape[1]:
            #     packet_i = 0
            # packet = sin30ref[:, packet_i * packetSize : (packet_i + 1) * packetSize]
            # packet = gauss_noise[:, packet_i * packetSize : (packet_i + 1) * packetSize]
            packet = np.random.normal(0, 1, (35, 512))
        elif target > 0 and target < 10:
            packet = eegdata[:, packet_i * packetSize : (packet_i + 1) * packetSize, target - 1]
        packet_pub.data = packet.reshape(35 * 512)
        pub.publish(packet_pub)
        print("talker", target)
        packet_i = packet_i + 1
        rate.sleep()

def callback_get_keys(msg):
    global target
    global packet_i
    print("I receive", msg.data)
    target = int(msg.data)
    packet_i = 0
		
if __name__ == '__main__':
    rospy.init_node('eeg_pub', anonymous=True)
    rospy.Subscriber('keys', String, callback_get_keys)
    talker()
    rospy.spin()