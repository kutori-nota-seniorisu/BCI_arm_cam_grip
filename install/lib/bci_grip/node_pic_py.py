#!/usr/bin/env python2
#coding=UTF-8
# license removed for brevity

#from ctypes.wintypes import POINT
from tokenize import Pointfloat
import time
import pyrealsense2 as rs
import numpy as np
import cv2
import json
import math
import rospy
from std_msgs.msg import String
from std_msgs.msg import Float64MultiArray
from std_msgs.msg import Float64
import sys
import math

pipeline = rs.pipeline()  
config = rs.config()   
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)  
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)   
profile = pipeline.start(config)  
align_to = rs.stream.color 
align = rs.align(align_to)


def get_aligned_images():
    frames = pipeline.wait_for_frames() 
    aligned_frames = align.process(frames)  
    aligned_depth_frame = aligned_frames.get_depth_frame() 
    color_frame = aligned_frames.get_color_frame()   

    ############### get camera intrinsics #######################
    intr = color_frame.profile.as_video_stream_profile().intrinsics  
    depth_intrin = aligned_depth_frame.profile.as_video_stream_profile().intrinsics  
    camera_parameters = {'fx': intr.fx, 'fy': intr.fy,
                         'ppx': intr.ppx, 'ppy': intr.ppy,
                         'height': intr.height, 'width': intr.width,
                         'depth_scale': profile.get_device().first_depth_sensor().get_depth_scale()
                         }
    #print(camera_parameters)
    # with open('./intr7insics.json', 'w') as fp:
    #     json.dump(camera_parameters, fp)
    #######################################################
    
    depth_image = np.asanyarray(aligned_depth_frame.get_data())  
    depth_image_8bit = cv2.convertScaleAbs(depth_image, alpha=0.03)  
    depth_image_3d = np.dstack((depth_image_8bit,depth_image_8bit,depth_image_8bit))  
    color_image = np.asanyarray(color_frame.get_data())  
    
    return intr, depth_intrin, color_image, depth_image, aligned_depth_frame

def read_resize_image(path, size=1.0):
    """
    读取原始图片文件并从新设置大小
     1) 使用imread读取文件
     2）使用resize从新设置文件大小
     3) 函数返回的是图片的原始数据，可理解为一个三维数组，每个维度分别表示长、宽、通道数，数组中的值表示图片每个像素点不同通道的取值
    """
 
    original_image = cv2.imread(path)
    if size != 1.0:
        height, width = original_image.shape[:2]
        size = (int(width * size), int(height * size))
        original_image = cv2.resize(original_image, size, interpolation=cv2.INTER_AREA)
 
    print(original_image)
    print(original_image.shape)
    print('shapeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee')
    return original_image

def get_hsv_image(original_image):
    """
      获取hsv色彩空间图片
       1) 先将BGR色彩转化为HSV色彩
      """
 
    hsv_image = cv2.cvtColor(original_image, cv2.COLOR_BGR2HSV)  # 将BGR色彩转化为HSV色彩
 
    cv2.imshow("HSV Image", hsv_image)
    print(hsv_image.shape)
    print('hsvshapeeeeeeeeeeeeeeeee')
 
    return hsv_image

def get_mask_image(hsv_image, lower, upper):
    """
    获取二值化图片
     1）通过阀值获取二值化图像
    """
    mask_image = cv2.inRange(hsv_image, lower, upper)  # 获取二值化图片
 
    cv2.imshow("Mask Image", mask_image)
    print(mask_image)
    print(mask_image.shape)
    print('maskshapeeeeeeeeeeeeeeeeeeeeeeeeeee')
 
    return mask_image

def get_morphology_image(mask_image):
    """
    对二值化图像进行形态学处理-消除噪音影响
      1) 先进行膨胀处理
         膨胀就是使用算法，来将图像的边缘扩大些。作用就是将目标的边缘或者是内部的坑填掉,去掉较小的孔洞
      2) 再进行腐蚀处理
         腐蚀：腐蚀会把物体的边界腐蚀掉，主要应用在去除白噪声，也可以断开连在一起的物体
    """
 
    kernel = np.ones((5, 5), np.uint8)
    dialationIamge = cv2.dilate(mask_image, kernel, iterations=1)  # 膨胀处理
    eroded_iamge = cv2.erode(dialationIamge, kernel, iterations=1)  # 腐蚀处理
 
    cv2.imshow("Eroded Iamge ", eroded_iamge)  # 显示形态学处理过后的图片
    return eroded_iamge

def get_contours(eroded_iamge):
    """
    获取光伏组件串图片的轮廓并在原始图像上绘制轮廓
       输入为形态学处理后的二值图像，黑色为背景，白色为目标
       cv2.RETR_EXTERNAL 只检测外轮廓
       cv2.CHAIN_APPROX_SIMPLE
    """
    # contours是轮廓本身，hierarchy 每条轮廓对应的属性（后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号）
    _,contours, hierarchy = cv2.findContours(eroded_iamge, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)  # 获取组件区域轮廓
 
    return contours

def talker():
    
    rospy.init_node('measure', anonymous=True)
    pub = rospy.Publisher('pos_ang', Float64MultiArray, queue_size=10)
    #pub2 = rospy.Publisher('angle', Float64MultiArray, queue_size=10)
    rate = rospy.Rate(10)
    #time.sleep(0.5)
    dis=[]
    camera_coordinate = []
    while not rospy.is_shutdown():
        intr, depth_intrin, rgb, depth, aligned_depth_frame = get_aligned_images() 
        print("============")
        print(aligned_depth_frame)
        camera_coordinate = np.zeros((5,3))
        array1 = [0 for x in range(4)]
        len_cen = 0
        for i in range(len(cen_p)):
            if(cen_p[i][0] != 0):
                len_cen = len_cen + 1
            else:
                break
        for i in range(0, len_cen, 1):
            print(i)
            disi = aligned_depth_frame.get_distance(int(cen_p[i][0]) , int(cen_p[i][1]))
            dis.append(disi)
            print('disiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii')
            #print("dis1: ", dis1)
            print("dis" + bytes(i) + ": " + str(dis[i]))
            #camera_coordinate.append(rs.rs2_deproject_pixel_to_point(depth_intrin, [cen_p[i][0], cen_p[i][1]], dis[i]))
            camera_coordinate[i][0], camera_coordinate[i][1], camera_coordinate[i][2]= rs.rs2_deproject_pixel_to_point(depth_intrin, [int(cen_p[i][0]), int(cen_p[i][1])], dis[i])
            print(camera_coordinate[i][0],camera_coordinate[i][1],camera_coordinate[i][2], angle[i])
            print('--------------------')
            
            array1.append(camera_coordinate[i][0])
            array1.append(camera_coordinate[i][1])
            array1.append(camera_coordinate[i][2])
            array1.append(angle[i])
            point = Float64MultiArray(data=array1)
            print('pppooo')
            print(point)
            pub.publish(point)	# 发布目标点坐标
            cv2.circle(original_image, (int(cen_p[i][0]) , int(cen_p[i][1])), 8, [255,0,255], thickness=-1)
            sys.exit()
            # 深度从img_depth[x, y]中获得
            #cv2.putText(original_image,"Dis:"+str(img_depth[int(cen_p[i][0]) , int(cen_p[i][1]])+" m", (40,40), cv2.FONT_HERSHEY_SIMPLEX, 1.2,[255,0,255])
            #cv2.putText(original_image,"X:"+str(np.float(vtx[y][x][0][0]))+" m", (80,80), cv2.FONT_HERSHEY_SIMPLEX, 1.2,[255,0,255])
            #cv2.putText(original_image,"Y:"+str(np.float(vtx[y][x][0][1]))+" m", (80,120), cv2.FONT_HERSHEY_SIMPLEX, 1.2,[255,0,255])
            #cv2.putText(original_image,"Z:"+str(np.float(vtx[y][x][0][2]))+" m", (80,160), cv2.FONT_HERSHEY_SIMPLEX, 1.2,[255,0,255])
            # 显示画面
            cv2.imshow('RealSence',original_image)
            key = cv2.waitKey(1)
            #pipeline.stop()
            
            rate.sleep()

         # 点的位置
    


    
#cv2.imshow('RGB image',original_image)  
    key = cv2.waitKey(1)

    


if __name__ == '__main__':
    path = '/home/edify-cx/code/bci_ws/src/bci_grip/src/4.png'
    original_image = read_resize_image(path, 0.3)  # 原始图像为3000X40000为方便观察，先将图片缩小5倍 既0.2

    hsv_image = get_hsv_image(original_image)  # 将rgb原始图像转化为hsv图像

    lower = np.array([75, 20, 15])
    upper = np.array([130, 255, 255])
    mask_image = get_mask_image(hsv_image, lower, upper)  # 获取二值化图像 通过HSV的高低阈值，提取图像部分区域

    eroded_iamge = get_morphology_image(mask_image)  # 对二值化的图像进行形态学处理
    
    contours = get_contours(eroded_iamge)  # 获取光伏组件轮廓区域
    #get_and_save_areas(contours, original_image)  # 将获取的轮廓区域截取图片并保存到文件
 
    cv2.drawContours(original_image, contours, -1, (0, 0, 255), 1)  # 在原图上绘制轮廓
    cv2.imshow("Original Image", original_image)  # 显示原始带轮廓图像


    #根据物体数量定义cen_p的长度
    cen_p = np.zeros((5,2))
    index = 0
    wid = []
    hei = []
    angle = []
    min_area = 2000
    d=0
    for cnt in contours:
        print(d)
        d=d+1
        imagearea = cv2.contourArea(cnt);
        if(imagearea > min_area):
            
            # 用绿色(0, 255, 0)来画出最小的矩形框架
            rect = cv2.minAreaRect(cnt)
            x, y = rect[0]
            w, h = rect[1]
            wid.append(w)
            hei.append(h)
            angle.append(rect[2])
            cen_p[index][0] = x
            cen_p[index][1] = y
            #cen_p.append(POINT(x+w/2, y+h/2))
            #cv2.rectangle(original_image, (int((x-w/2)*cos(rect[2])), int(y-h/2)), (int(x+w/2), int(y+h/2)), (0, 255, 0), 1)
            ang = angle[index] * np.pi / 180
            x1 = int(x + (w/2)*np.cos(ang) - (h/2)*np.sin(ang))
            y1 = int(y + (w/2)*np.sin(ang) + (h/2)*np.cos(ang))
            x2 = int(x + (w/2)*np.cos(ang) + (h/2)*np.sin(ang))
            y2 = int(y + (w/2)*np.sin(ang) - (h/2)*np.cos(ang))
            x3 = int(x - (w/2)*np.cos(ang) + (h/2)*np.sin(ang))
            y3 = int(y - (w/2)*np.sin(ang) - (h/2)*np.cos(ang))
            x4 = int(x - (w/2)*np.cos(ang) - (h/2)*np.sin(ang))
            y4 = int(y - (w/2)*np.sin(ang) + (h/2)*np.cos(ang))
            #color = (30 * i, 0, 255 - 30 * i)
            cv2.line(original_image, (x1, y1), (x2, y2), (0, 255, 0))
            cv2.line(original_image, (x2, y2), (x3, y3), (0, 255, 0))
            cv2.line(original_image, (x3, y3), (x4, y4), (0, 255, 0))
            cv2.line(original_image, (x4, y4), (x1, y1), (0, 255, 0))
            index+=1

            
    if(index == 0):
        print("the process of findcontours fail!")
        sys.exit()
    try:
        talker()
    except rospy.ROSInterruptException:
        pass

#    
#    img1 = cv2.imread('/home/zff/code/data/model.png')
#    orb = cv2.ORB_create()
#    
    # FLANN_INDEX_KDTREE = 1
    # indexParams = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
    # searchParams = dict(checks=50)
#    FLANN_INDEX_LSH = 6
#    indexParams = dict(algorithm = FLANN_INDEX_LSH, table_number = 6, key_size = 12, multi_probe_level = 1)
#    searchParams = dict(checks = 200)
#    try:
#        talker()
#    except rospy.ROSInterruptException:
#        pass
