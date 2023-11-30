#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Bool
from std_msgs.msg import UInt16

# 需要添加路径
import sys
sys.path.append("/home/sd/BCI_arm_cam_grip/src/online_analysis/scripts")

import my_function
import rospy
import numpy as np
from scipy import signal
from sklearn.cross_decomposition import CCA

# 相关变量及参数设置
# 采样频率，默认为2048Hz
sampleRate = 2048
# 数组缓存区大小
BUFFSIZE = sampleRate * 3
# 频率序列
freqList = [9, 10, 11, 12, 13, 14, 15, 16, 17]
# 每个数据包大小
packetSize = 512
# 分析间隔：0.5s
anaInter = 0.5
# 分类结果阈值
r_threshold = 0.6
# 选用分析方法，method = 1:CCA，method = 2:FBCCA
method = 1

# 参数：降采样
downSamplingNum = 8
downSampleRate = sampleRate / downSamplingNum
downBuffSize = int(BUFFSIZE / downSamplingNum)

# 参数：50Hz陷波滤波器
# 将要被移除的频率 (Hz)
f_notch = 50
Ts = 1.0 / downSampleRate
alpha = -2 * np.cos(2 * np.pi * f_notch * Ts)
beta = 0.95
# 构造滤波器
notch_b = [1, alpha, 1]
notch_a = [1, alpha * beta, beta**2]

# 参数：带通滤波器
# 通带阻带截止频率
Wp = [7.0 / (downSampleRate / 2), 70.0 / (downSampleRate / 2)]
Ws = [5.0 / (downSampleRate / 2), 80.0 / (downSampleRate / 2)]
# 通带最大衰减 [dB]
Rp = 3
# 阻带最小衰减 [dB]
Rs = 60
N, Wn = signal.cheb1ord(Wp, Ws, Rp, Rs)
# peak-to-peak ripple with R dB in the passband
bp_R = 0.5
B, A = signal.cheby1(N, bp_R, Wn, "bandpass")

# 五个子带
num_fbs = 5
# 权重系数
a_fbcca = 1.25
b_fbcca = 0.25
fb_coefs = np.array(
	[(n + 1.0)**(-a_fbcca) + b_fbcca for n in range(0, num_fbs)])

# 生成参考信号
num_harms = 4
w_sincos = 0
y_ref = my_function.sincosref(
	freqList,
	downSampleRate,
	downBuffSize,
	num_harms,
	w_sincos)
# 标志相机启动与否的变量，为 false 时未启动，为 true 时启动
camera_on = False

# 用于分析的数据数组
data_used = np.array([])

# 用于存储分析结果
res_arr = np.zeros(4)

result_pub = rospy.Publisher("/ResultNode", UInt16, queue_size=10)
state_result_pub = rospy.Publisher("/StateResultNode", Bool, queue_size=10)
camera_on_pub = rospy.Publisher("/PicSubSig", Bool, queue_size=10)

# 获取采样频率
def callback_get_rate(rate):
	global sampleRate
	sampleRate = rate.data
	rospy.loginfo("sample rate is : %f", sampleRate)

# 获取数据包
def callback_get_packet(data):
	# 把一维数组转换成二维数组
	rawdata = np.array(data.data[:]).reshape(512, 35).T
	# 判断，是进行初始化，还是将数据拼接
	global data_used, camera_on
	global res_arr
	if data_used.size == 0:
		data_used = rawdata
	else:
		data_used = np.hstack((data_used, rawdata))
		# 用作差的方式判断接收的数据包数量，每0.5s进入一次分析
		delta = data_used.shape[1] - BUFFSIZE
		if delta >= 0:
			if delta % (anaInter * sampleRate) == 0:
				data_used = data_used[:, -BUFFSIZE:]

	if data_used.shape[1] == BUFFSIZE:
		print("analysis start")
		# 当数组长度超过缓存长度，则进行处理
		# 选择导联
		ch_used = [20, 24, 25, 26, 27, 28, 29, 30, 31]
		# data used
		data_chused = data_used[ch_used, :]
		# the number of channels usd
		channel_usedNum = len(ch_used)

		# data pre-processing
		# downsampling
		data_downSample = signal.decimate(
			data_chused, downSamplingNum, ftype='fir')
		# 50Hz notch filter
		data_50hz = signal.filtfilt(notch_b, notch_a, data_downSample)
		# remove baseline
		data_removeBaseline = data_50hz - \
			np.median(data_50hz, -1).reshape(channel_usedNum, 1)
		# bandpass filter
		data_bandpass = signal.filtfilt(B, A, data_removeBaseline)

		# 存储分类结果
		result = 0

		# 现在方法二的用时是方法一的十倍
		if method == 1:
			# CCA分析
			num_class_cca = len(freqList)
			# 用于存储数据与参考信号的相关系数
			r_cca = np.zeros((num_class_cca))
			for class_i in range(0, num_class_cca):
				refdata_cca = y_ref[class_i].T
				cca = CCA(n_components=1)
				cca.fit(data_bandpass.T, refdata_cca)
				U, V = cca.transform(data_bandpass.T, refdata_cca)
				r_cca[class_i] = np.corrcoef(U[:, 0], V[:, 0])[0, 1]
			print("CCA:", r_cca)

			# 获取相关系数排序
			index_rcca = np.argsort(r_cca)
			# 判断本次分类是否有效
			d = r_cca[index_rcca[-1]] - r_cca[index_rcca[-2]]
			print("差值：", d)
			if d > 0.08:
				# 获取相关系数最大的索引并查找对应频率
				# 将查找到的频率添加到结果数组中
				# 四次中三次相同则可确定
				i_rcca = np.argmax(r_cca)
				result = freqList[i_rcca]
				print("本次分类有效，结果为", result)
			else:
				print("本次分类无效")
				# 跳过下面所有环节

		elif method == 2:
			# FBCCA
			num_class_fbcca = len(freqList)
			# eigenvalue_r_fbcca:存储子带数据与各个参考信号的相关系数，num_fbs x
			# num_class_fbcca的数组
			eigenvalue_r_fbcca = np.zeros((num_fbs, num_class_fbcca))

			# num_fbs:子带数量
			for fb_i in range(0, num_fbs):
				# 生成滤波器并对原始数据滤波
				data_fbcca = my_function.filterbank(
					data_bandpass, downSampleRate, fb_i)
				# 子带数据与参考数据进行CCA分析
				for class_i in range(0, num_class_fbcca):
					refdata_fbcca = y_ref[class_i].T
					fbcca = CCA(n_components=1)
					fbcca.fit(data_fbcca.T, refdata_fbcca)
					U, V = fbcca.transform(data_fbcca.T, refdata_fbcca)
					eigenvalue_r_fbcca[fb_i, class_i] = np.corrcoef(U[:, 0], V[:, 0])[
						0, 1]
			# 计算加权后的相关系数
			r_fbcca = fb_coefs @ (eigenvalue_r_fbcca ** 2)
			print("FBCCA:", r_fbcca)
			index_class_cca = np.argmax(r_fbcca)
			result = freqList[index_class_cca]

		# 四次中三次相同
		res_arr = np.append(res_arr, result)[1:]
		print("res array:", res_arr)
		real_res = int(my_function.find(res_arr))
		if real_res == 0:
			print("本次未分析出结果！！")
		else:
			print("分析成功！！")
			print("real result is", real_res)

		if real_res == 15:
			# do something
			print("相机启动频率为", real_res)
			camera_state = Bool()
			camera_on = True
			camera_state.data = camera_on
			state_result_pub.publish(camera_state)
			camera_on_pub.publish(camera_state)
			# time.sleep(0.5)
			# print("延时0.5")
		if camera_on and real_res != 0 and real_res != 15:
			print("本次实验结果为", real_res)
			res_pub = UInt16()
			res_pub.data = real_res
			result_pub.publish(res_pub)

		print("analysis finish\n")


def listener():
	# In ROS, nodes are uniquely named. If two nodes with the same
	# name are launched, the previous one is kicked off. The
	# anonymous=True flag means that rospy will choose a unique
	# name for our 'listener' node so that multiple listeners can
	# run simultaneously.
	rospy.init_node('analysis', anonymous=True)

	camera_init = Bool()
	camera_init.data = False
	state_result_pub.publish(camera_init)

	rospy.Subscriber("samplerate", UInt16, callback_get_rate)
	rospy.Subscriber("packet", Float32MultiArray, callback_get_packet)
	# rospy.Subscriber("packet1", Float32MultiArray, callback2)

	# spin() simply keeps python from exiting until this node is stopped
	rospy.spin()


if __name__ == '__main__':
	listener()
