#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import rospy
from std_msgs.msg import String
from std_msgs.msg import UInt16
from std_msgs.msg import Float32MultiArray
from scipy import signal, fft

from PySide2.QtWidgets import QApplication
from PySide2.QtUiTools import QUiLoader
from PySide2.QtCore import Signal, QObject

import pyqtgraph as pg
import numpy as np

# check box 是否勾选的标志变量
base_check = False
notch_check = False
low_check = False
high_check = False

# combo box 当前索引
current_index = -1

# 采样频率，默认为2048Hz
sampleRate = 2048

# 通道数量，默认为35
chanNum = 35

# 数据包长度，默认为512
packetLen = 512

# 存放显示的数据
wave_data = 0

# 显示的数据长度 3s*2048Hz
showLen = 0

# 参数：50Hz陷波滤波器
# 将要被移除的频率 (Hz)
f_notch = 50
Ts = 1.0 / sampleRate
alpha = -2 * np.cos(2 * np.pi * f_notch * Ts)
beta = 0.95
# 构造滤波器
notch_b = [1, alpha, 1]
notch_a = [1, alpha * beta, beta**2]

# 需要手动创建信号的类，然后才可将信号与槽相互连接
class MySignal(QObject):
	signal = Signal(Float32MultiArray)

# 定义了一个槽函数，绘制波形
def wave_draw(val):
	global base_check, notch_check, high_check, low_check
	global current_index
	global packetLen, wave_data, showLen

	# t 为时间刻度
	t = np.arange(0,showLen)

	nEegChan = val.shape[0]
	dDeltaY = 1.0 / nEegChan

	aAvg = np.mean(val, -1)
	# aMax = np.max(val, -1)
	# aMin = np.min(val, -1)
	
	# wave_data = val
	# 基线移动
	if base_check:
		# print("in base check")
		for i in range(0, nEegChan):
			val[i] = val[i] - aAvg[i]
	# 50Hz陷波滤波
	if notch_check:
		# print("in notch check")
		val = signal.filtfilt(notch_b, notch_a, val)
	# 低通滤波
	if low_check:
		N = 8
		Wn = ui.spinBox_low.value() / (sampleRate / 2)
		B, A = signal.cheby1(N, 0.5, Wn, "low")
		val = signal.filtfilt(B, A, val)
	# 高通滤波
	if high_check:
		N = 8
		Wn = ui.spinBox_high.value() / (sampleRate / 2)
		B, A = signal.cheby1(N, 0.5, Wn, "high")
		val = signal.filtfilt(B, A, val)

	wave_data = np.hstack((wave_data, val))
	wave_data = wave_data[:, -showLen:]
	aMax = np.max(wave_data, -1)
	aMin = np.min(wave_data, -1)

	p1.clear()
	# 曲线绘制
	for i in range(0, nEegChan):
		# 自适应范围
		dAutoScale = dDeltaY / ((aMax[i] - aMin[i]) * 1.25)
		# 偏移量
		nYOffset = (i + 0.5) * dDeltaY
		# 绘制
		p1.plot(t, wave_data[i] * dAutoScale + nYOffset)
	
	p2.clear()
	# 曲线绘制
	if current_index != -1:
		# print("I draw picture 2")
		auto_scale_single = dDeltaY / ((aMax[current_index] - aMin[current_index]) * 1.25)
		p2.plot(t, wave_data[current_index] * auto_scale_single)

	p3.clear()
	# 曲线绘制
	if current_index != -1:
		# print("I draw picture 3")
		Ts = 1 / sampleRate
		L = showLen
		# 频率分辨率
		delta_f = sampleRate / L
		# 傅里叶变换
		fft_x = fft.fft(wave_data[current_index])
		# 双边谱的幅值恢复
		pows2_x = np.abs(fft_x / L)
		# 双边谱转单边谱
		fft_wave = pows2_x[0 : int(L / 2)]
		fft_wave[1 : int(L / 2)] = 2 * fft_wave[1 : int(L / 2)]
		# 频率坐标
		freqs_x = np.arange(0, int(L / 2)) * delta_f
		p3.plot(freqs_x, fft_wave)

# 实例化信号类的对象，然后将该对象的信号与对应的槽函数连接，此处槽函数为 test_func1
mysi = MySignal()
mysi.signal.connect(wave_draw)

# 获取采样频率
def callback_get_rate(rate):
	global sampleRate, showLen
	sampleRate = rate.data
	print("采样频率为：", sampleRate)
	showLen = 3 * sampleRate
	

# 获取通道标签
def callback_get_chan(chan):
	print("收到标签：", chan.data)
	ui.comboBox.addItem(chan.data)
	ui.comboBox_2.addItem(chan.data)

# 获取通道数量
def callback_get_chanNum(num):
	global chanNum, sampleRate, wave_data, showLen
	chanNum = num.data
	print("通道数量为：", chanNum)
	wave_data = np.zeros((chanNum, showLen))

# 获取数据包长度
def callback_get_sampleNum(sampleNum):
	global packetLen
	packetLen = sampleNum.data
	print("数据包长度为：", packetLen)

# 定义了 ros 接收节点的回调函数，接收到数据包后发送信号，由槽函数进行绘制
def callback_get_packet(data):
	global mysi, chanNum
	# 把一维数组转换成二维数组
	rawdata = np.array(data.data[:]).reshape(packetLen, chanNum).T
	# print(rawdata.shape)
	mysi.signal.emit(rawdata)

rospy.init_node('wave_show', anonymous=True)
rospy.Subscriber("packet", Float32MultiArray, callback_get_packet)
rospy.Subscriber("samplerate", UInt16, callback_get_rate)
rospy.Subscriber("channum", UInt16, callback_get_chanNum)
rospy.Subscriber("samplenum", UInt16, callback_get_sampleNum)
rospy.Subscriber("chanlabel", String, callback_get_chan)

def on_checkBox_base_stateChanged(state):
	global base_check
	base_check = state

def	on_checkBox_notch_stateChanged(state):
	global notch_check
	notch_check = state

def on_checkBox_low_stateChanged(state):
	global low_check
	low_check = state
	ui.spinBox_low.setEnabled(state)

def	on_checkBox_high_stateChanged(state):
	global high_check
	high_check = state
	ui.spinBox_high.setEnabled(state)

def on_checkBox_base_2_stateChanged(state):
	global base_check
	base_check = state

def	on_checkBox_notch_2_stateChanged(state):
	global notch_check
	notch_check = state

def on_checkBox_low_2_stateChanged(state):
	global low_check
	low_check = state
	ui.spinBox_low_2.setEnabled(state)

def	on_checkBox_high_2_stateChanged(state):
	global high_check
	high_check = state
	ui.spinBox_high_2.setEnabled(state)

def on_comboBox_indexChanged(index):
	global current_index
	current_index = index
	print("the 1st index is changed:", index)

def on_comboBox_2_indexChanged(index):
	global current_index
	current_index = index
	print("the 2nd index is changed:", index)

def on_tabWidget_currentChanged(index):
	print("tab widget changed!")
	global base_check, notch_check, low_check, high_check
	global current_index
	if index == 0:
		base_check = ui.checkBox_base.isChecked()
		notch_check = ui.checkBox_notch.isChecked()
		low_check = ui.checkBox_low.isChecked()
		high_check = ui.checkBox_high.isChecked()
		current_index = ui.comboBox.currentIndex()
	elif index == 1:
		base_check = ui.checkBox_base_2.isChecked()
		notch_check = ui.checkBox_notch_2.isChecked()
		low_check = ui.checkBox_low_2.isChecked()
		high_check = ui.checkBox_high_2.isChecked()
		current_index = ui.comboBox_2.currentIndex()


app = QApplication([])
loader = QUiLoader()
# pyside2 一定要使用registerCustomWidget 
# 来注册 ui 文件中的第三方控件，这样加载的时候
# loader才知道第三方控件对应的类，才能实例化对象
loader.registerCustomWidget(pg.GraphicsLayoutWidget)
ui = loader.load("/home/sd/BCI_arm_cam_grip/src/wave_show/ui/ui_waveshow.ui")
# widget 是控件名称，需要注意
pw = ui.widget
pw.setBackground('w')
p1 = pw.addPlot(left = "labels", bottom = "time", title = "all channels", row = 0, col = 0)
p1.showGrid(x = True, y = True)
p1.getAxis('left').setPen('#000000') # 坐标轴上色
p1.getAxis('bottom').setPen('#000000') # 坐标轴上色
p2 = pw.addPlot(left = "label", bottom = "time", title = "single channel", row = 1, col = 0)
p2.showGrid(x = True, y = True)
p2.getAxis('left').setPen('#000000') # 坐标轴上色
p2.getAxis('bottom').setPen('#000000') # 坐标轴上色
p3 = pw.addPlot(left = "label", bottom = "freq", title = "fft", row = 3, col = 0)
p3.showGrid(x = True, y = True)
p3.getAxis('left').setPen('#000000') # 坐标轴上色
p3.getAxis('bottom').setPen('#000000') # 坐标轴上色

# 信号与槽的连接
ui.checkBox_base.stateChanged.connect(on_checkBox_base_stateChanged)
ui.checkBox_notch.stateChanged.connect(on_checkBox_notch_stateChanged)
ui.checkBox_low.stateChanged.connect(on_checkBox_low_stateChanged)
ui.checkBox_high.stateChanged.connect(on_checkBox_high_stateChanged)
ui.checkBox_base_2.stateChanged.connect(on_checkBox_base_2_stateChanged)
ui.checkBox_notch_2.stateChanged.connect(on_checkBox_notch_2_stateChanged)
ui.checkBox_low_2.stateChanged.connect(on_checkBox_low_2_stateChanged)
ui.checkBox_high_2.stateChanged.connect(on_checkBox_high_2_stateChanged)
ui.comboBox.currentIndexChanged.connect(on_comboBox_indexChanged)
ui.comboBox_2.currentIndexChanged.connect(on_comboBox_2_indexChanged)
ui.tabWidget.currentChanged.connect(on_tabWidget_currentChanged)

ui.show()
app.exec_()
