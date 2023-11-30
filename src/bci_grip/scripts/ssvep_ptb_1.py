#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
# 用对比度实现，范围是[-1,1]
# 用两帧之间的间隔时间为时间增量，并创建对应序列
import random
import numpy as np
import rospy
import scipy.signal as signal
from psychopy import visual, event, core
import scipy.signal as signal
import cv2
import sys
import math
from std_msgs.msg import String, Bool, Float64MultiArray, UInt16
from threading import Thread, current_thread
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

sig = 0

def mstoframe(ms, fps):
	return np.round(ms * fps / 1000).astype(int)

def StateResult_Callback(msg):
	global sig
	if msg.data == True:
		sig =  1

def Picture_Callback(msg):
	global Pic
	Pic = CvBridge().imgmsg_to_cv2(msg, "bgr8")

def PositionLength_Callback(msg):
	global Pos
	ReceivePosLen = np.array(msg.data)
	# 将 ReceivePosLen 重构为 (length(ReceivePosLen)/3,3) 的新的矩阵 Pos
	# len(ReceivePosLen)/3为物块个数，3表示位置x、y和矩形边长
	print(ReceivePosLen.shape[0])
	Pos = ReceivePosLen.reshape(int(ReceivePosLen.shape[0] / 3), 3)
	# Pos = Pos.T
	
def GripSig_Callback(msg):
	global changesig
	changesig = msg.data
	
def Result_Callback(msg):
	global result
	result = msg.data

	
def ssvep_pre():
	global sig, Pic, Pos, changesig, result, Flash_Position_Black, object_num
	changesig = 1
	result = 0
	bg_colour = [-1, -1, -0.25]
	# 【PTB窗口显示大小】
	win = visual.Window(
		size=[1920/3*2, 1080/3*2],
		# size=[640, 480],
		units="pix",
		fullscr=False,
		color=[-1,-1,-1], # black(-1,-1,-1)  white(1,1,1)
	)
	screenXpixels, screenYpixels = win.size   # Get the size of the on screen window 
	Msperframe = win.getMsPerFrame()  # 刷新间隔 16.667 ms
	ifi = win.getMsPerFrame()[0] / 1000 # 刷新间隔 0.0167 ms
	# print('Msperframe', Msperframe, "ms")
	# fps = np.round(1000 / Msperframe[0]).astype(int)  # 每秒刷新率 % 60Hz
	# FPS = win.getActualFrameRate()
	# print("your screen's fps is ", fps, "Hz", 1.0/fps,"s" , "FPS is ", FPS, "1/FPS is ", 1.0/FPS)
	
	# Load the PseudoKey Picture
	path = '/home/sd/BCI_arm_cam_grip/src/bci_grip/scripts/' 
	theImage_PseudoKey = path + 'PseudoKey.jpg'
	Image_PseudoKey = cv2.imread(theImage_PseudoKey, cv2.IMREAD_UNCHANGED)
	Image_PseudoKey = cv2.resize(Image_PseudoKey, [200,200], cv2.INTER_CUBIC)    # 双三次样条插值
	ImageSize_u_PseudoKey = Image_PseudoKey.shape[1] # 200 -x
	ImageSize_v_PseudoKey = Image_PseudoKey.shape[0] # 200 -y
	cv2.imwrite(path + 'PseudoKey_rs.jpg', Image_PseudoKey)
	theImage_PseudoKey = path + 'PseudoKey_rs.jpg'   
	
	xCenter, yCenter = 0, 0 # 屏幕中心
	# Position of  picture is [Center_X, Center_Y, Width, Height]
	Position_pseudo_LU = 0.5 * np.array([-screenXpixels, screenYpixels, 0, 0]) + 0.5 * np.array([ImageSize_u_PseudoKey, -ImageSize_v_PseudoKey, 0, 0]) + np.array([0, 0, ImageSize_u_PseudoKey, ImageSize_v_PseudoKey])   # 左上
	Position_pseudo_RU = 0.5 * np.array([screenXpixels, screenYpixels, 0, 0]) + 0.5 * np.array([-ImageSize_u_PseudoKey, -ImageSize_v_PseudoKey, 0, 0]) + np.array([0, 0, ImageSize_u_PseudoKey, ImageSize_v_PseudoKey])  # 右上
	Position_pseudo_RD = 0.5 * np.array([screenXpixels, -screenYpixels, 0, 0]) + 0.5 * np.array([-ImageSize_u_PseudoKey, ImageSize_v_PseudoKey, 0, 0]) + np.array([0, 0, ImageSize_u_PseudoKey, ImageSize_v_PseudoKey])   # 右下
	Position_pseudo_LD = 0.5 * np.array([-screenXpixels, -screenYpixels, 0, 0]) + 0.5 * np.array([ImageSize_u_PseudoKey, ImageSize_v_PseudoKey, 0, 0]) + np.array([0, 0, ImageSize_u_PseudoKey, ImageSize_v_PseudoKey])   # 左下
	Flash_Position_Pseudo = np.zeros((4, 4))
	Flash_Position_Pseudo[0][:] = Position_pseudo_LU
	Flash_Position_Pseudo[1][:] = Position_pseudo_RU
	Flash_Position_Pseudo[2][:] = Position_pseudo_RD
	Flash_Position_Pseudo[3][:] = Position_pseudo_LD
	# print(Flash_Position_Pseudo[0][:])
	amplitude = 0.5 # 振幅
	freq_pre = 15
	staP_pre = 0.0
	angF_pre = 2 * np.pi * freq_pre
	wait_text_1=visual.TextStim(
							win=win,
							text='Press anykey to continue.',
							color=[1, 1, 1],
							colorSpace='rgb',
							pos=(0,0),
							height=60
							)
	wait_text_2=visual.TextStim(
							win=win,
							text='Wait for picture to come.',
							color=[1, 1, 1],
							colorSpace='rgb',
							pos=(0,0),
							height=60
							)
	wait_text_3=visual.TextStim(
							win=win,
							text='The experiment is end!',
							color=[1, 1, 1],
							colorSpace='rgb',
							pos=(0,0),
							height=60
							)
	block_PseudoKey = [0 for i in range(4)]  # 初始化
	for i in range(4):
		block_PseudoKey[i] = visual.ImageStim(
											win=win, 
											units='pix',
											image=theImage_PseudoKey, 
											pos=[Flash_Position_Pseudo[i][0], Flash_Position_Pseudo[i][1]],
											size=[Flash_Position_Pseudo[i][2], Flash_Position_Pseudo[i][3]]
											)
	print("image",Image_PseudoKey.shape)
	# seq = [[0 for i in range(fps)] for i in range(5)]  # 创建对于帧数的数组
	# n = np.arange(0, fps)
	# for i in range(4):
	# 	seq[i] = [(math.sin(angF_pre * (j / fps))) for j in range(n.shape[0])]  # 利用math.sin转换成正弦波，并且利用offset将幅值转换到0～1,进而利用对比度实现闪烁。
	
	while 1:
		wait_text_1.draw()
		win.flip()
		if event.getKeys(keyList=['space', 'escape']):
			break
	time = 0
	# 伪密钥阶段
	while 1:
		if event.getKeys(keyList=['space', 'escape']) or sig == 1:
			break
		for num in range(4):
			block_PseudoKey[num].contrast = np.sin(angF_pre * time)
			block_PseudoKey[num].draw()
		time = time + ifi
		win.flip()
		
	# 伪密钥检测后，进入了下一个场景图片接收与显示的阶段
	# After the detection of the pseudo key,
	# the next stage of picture reception and display is entered
	win.flip()  # 将屏幕win涂成black
	# 对图片与位置信息进行初始化
	Pic = cv2.imread(path+ 'CameraShooting.jpg')  # 初始化一下Pic 690x690x3 uint8
	Pos = np.array([[-50, 0, 50], [0, 0, 50], [50, 0, 50]])
	# 等待图片何位置信息的订阅
	duration_s = 3.0  
	clock = core.Clock()
	while clock.getTime() < duration_s:
		wait_text_2.draw()
		win.flip()
		if event.getKeys(keyList=['space', 'escape']):
			break
		
	# 尺寸重新设置，将订阅的图片占满屏幕
	height, width, chan = Pic.shape   # 读取图片三维矩阵大小，顺序为 高度 宽度 通道数 height 480; width 640
	ratio = 1.5
	resize_y = int(width*ratio) #960
	resize_x = int(height*ratio) #720
	ExpScene = cv2.resize(Pic, [resize_y, resize_x], cv2.INTER_CUBIC)   # [480,640]--->[720,960]
	cv2.imwrite(path + 'pic_rs.jpg', ExpScene)
	ExpSceneLocation = path + 'pic_rs.jpg'
	Position_ExpScene = np.array([xCenter, yCenter, resize_x, resize_y])
	delta_pos = np.array([xCenter - resize_y/2, yCenter + resize_x/2, 0, 0])    # 图像中物块的位置相对屏幕中心的图像的偏移量
	# delta_pos[-960/2=-480, 720/2=360, 0, 0]
	ExpSceneTexture = visual.ImageStim(
										win=win, 
										image=ExpSceneLocation, 
										pos=[Position_ExpScene[0], Position_ExpScene[1]],
										# size=[Position_ExpScene[2], Position_ExpScene[3]]
										)
	win.flip()
	# 黑色代表图片中的物块
	BlackImageLocation = path + 'target_Black.jpg' 
	BlackImage = cv2.imread(BlackImageLocation)
	BlackImage = cv2.resize(BlackImage, [100, 100], cv2.INTER_CUBIC) 
	cv2.imwrite(path + 'target_Black_rs.jpg', BlackImage)
	BlackImageLocation = path + 'target_Black_rs.jpg' 
	# White 作为衬底
	WhiteImageLocation = path + 'target_White.jpg'
	WhiteImage = cv2.imread(WhiteImageLocation)
	WhiteImage = cv2.resize(WhiteImage, [100, 100], cv2.INTER_CUBIC) 
	cv2.imwrite(path + 'target_White_rs.jpg', WhiteImage)
	WhiteImageLocation = path + 'target_White_rs.jpg' 
	# 红色代表注释选择后的目标
	RedImageLocation = path + 'SmallRed.jpg'
	RedImage = cv2.imread(RedImageLocation)
	RedImage = cv2.resize(RedImage, [100, 100], cv2.INTER_CUBIC) 
	cv2.imwrite(path + 'target_Red_rs.jpg', RedImage)
	RedImageLocation = path + 'target_Red_rs.jpg' 
	# 对图片中的物块进行闪烁刺激
	object_frequency = np.array([9, 10, 11, 12, 13, 14])   # 6个频率，最多6个物块
	object_angFreq = np.zeros(object_frequency.shape[0])
	for i in range(object_frequency.shape[0]):
		object_angFreq[i] = 2 * np.pi * object_frequency[i]
	object_startPhase = np.array([0.0, 0.25, 0.5, 0.75, 1.0, 1.25]) * np.pi    #  6个相位
	imageTexture_White = visual.ImageStim(win=win, image=WhiteImageLocation)
	imageTexture_Red = visual.ImageStim(win=win, image=RedImageLocation)
	# seq1 = [[0 for i in range(fps)] for i in range(object_frequency.shape[0])]  # 创建对于帧数的数组
	# n = np.arange(0, fps)
	# print('nppy', object_frequency.shape[0])
	# for i in range(object_frequency.shape[0]):
	# 	seq1[i] = [(math.sin(object_angFreq[i] * (j / fps)) * amplitude+ amplitude) for j in range(n.shape[0])]  # 利用math.sin转换成正弦波，并且利用offset将幅值转换到0～1,进而利用对比度实现闪烁。
	time = 0
	while 1:
		if event.getKeys(keyList=['space', 'escape']):
			break
		object_num = Pos.shape[0]
		# print("Number of objects identified is ", object_num)
		if object_num==0:   # 如果未识别到物体，说明场景中物块都已经抓取完毕，则跳出循环
			break
		# 在一轮小循环中，如果没有抓取完毕，则changesig仍为0，只有在changesig为1时（抓取完毕）才会切换图片
		if changesig == 1:  # 每一抓取实验前的初始化
			jump_while = 1
			while (jump_while):
				object_num = Pos.shape[0] # Pos_size[640,480,3]
				height, width, chan = Pic.shape   # 读取图片三维矩阵大小，顺序为 高度 宽度 通道数  height 480; width 640
				ratio_2 = 1.5
				resize_y2 = int(height * ratio_2) # 480*1.5=720
				resize_x2 = int(width * ratio_2)  # 640*1.5=960
				Flash_Position_Black = np.zeros((object_num, 4))
				imageTexture_Black = visual.ImageStim(win=win, image=BlackImageLocation)
				imageTexture_White = visual.ImageStim(win=win, image=WhiteImageLocation)
				for i in range(object_num):
					print("object")
					print(object_num)
					print("pos_length")
					print(Pos.shape[0])
					if  object_num != Pos.shape[0]:
						break
					else :
						Flash_Position_Black[i][:] = [ratio_2 * Pos[i][0], -ratio_2 * Pos[i][1] ,10, 20] + delta_pos # 每一个物块的位置 # delta_pos[-960/2=-480, 720/2=360, 0, 0]
						jump_while = 0
			
			ExpScene = cv2.resize(Pic, [resize_x2, resize_y2], cv2.INTER_CUBIC)   # [480,640]--->[720,960]
			cv2.imwrite(path + 'pic_rs.jpg', ExpScene)
			ExpSceneLocation = path + 'pic_rs.jpg'
			ExpSceneTexture = visual.ImageStim(win=win, image=ExpSceneLocation)
			Position_ExpScene = np.array([xCenter, yCenter, resize_x2, resize_y2])
			changesig = 0   # 重新变为不可改变图片的模式

		# red 用来存储第几张图片将变成红色，如果没有响应的结果，red为0
		red = -1
		for i in range(object_num):
			if object_frequency[i] == result:
				red = i
				break
		ExpSceneTexture.pos = [Position_ExpScene[0], Position_ExpScene[1]]
		# ExpSceneTexture.size = [Position_ExpScene[2], Position_ExpScene[3]]
		ExpSceneTexture.draw()
		for i in range(object_num):
			if red != -1:    # 如果red非0，即已经接收到结果信息
				if i == red:
					imageTexture_Red.pos = [Flash_Position_Black[i][0], Flash_Position_Black[i][1]]
					imageTexture_White.pos = [Flash_Position_Black[i][0], Flash_Position_Black[i][1]]
					imageTexture_White.draw()
					imageTexture_Red.draw()
				else:
					imageTexture_Black.pos = [Flash_Position_Black[i][0], Flash_Position_Black[i][1]]
					# imageTexture_Black.size = [Flash_Position_Black[i][2], Flash_Position_Black[i][3]] # 这一行重新设置了黑色色块的大小
					imageTexture_Black.contrast = np.sin(object_angFreq[i] * time)
					# imageTexture_White.pos = [Flash_Position_Black[i][0], Flash_Position_Black[i][1]]
					# imageTexture_White.draw()
					imageTexture_Black.draw()
			else:
				imageTexture_Black.pos = [Flash_Position_Black[i][0], Flash_Position_Black[i][1]]
				# imageTexture_Black.size = [Flash_Position_Black[i][2], Flash_Position_Black[i][3]] # 这一行重新设置了黑色色块的大小
				imageTexture_Black.contrast = np.sin(object_angFreq[i] * time)
				# imageTexture_White.pos = [Flash_Position_Black[i][0], Flash_Position_Black[i][1]]
				# imageTexture_White.draw()
				imageTexture_Black.draw()
				# print(imageTexture_Black.pos)
				# print("pos")
				# print(Pos[i][0])
				# print(Pos[i][1])
				# print("delta")
				# print(delta_pos )
				# print(Pos)
		win.flip()
		time = time + ifi
	win.flip()
	wait_text_3.draw()
	win.flip()
	event.waitKeys()
	win.close()
	rospy.signal_shutdown("Congratulation! The experiment is end!")
	
if __name__ == '__main__':
	try:
		# Python 语言初始化 ROS 节点
		rospy.init_node('ssvep_ptb', anonymous=True)
		rospy.Subscriber("/StateResultNode", Bool, StateResult_Callback)
		rospy.Subscriber("/PictureNode", Image, Picture_Callback)   # 开启图像订阅节点
		rospy.Subscriber("/PositionLengthNode", Float64MultiArray, PositionLength_Callback)
		rospy.Subscriber("/GripSig", Bool, GripSig_Callback)
		rospy.Subscriber("/ResultNode", UInt16, Result_Callback)
		thread_ssvep = Thread(target=ssvep_pre, args="", name="线程1")
		thread_ssvep.setDaemon(True)
		thread_ssvep.start()
		rospy.spin()
	except rospy.ROSInterruptException:
		print("program interrupted before completion", file=sys.stderr)