#!/usr/bin/env python2
# license removed for brevity

import pyrealsense2 as rs
import numpy as np
import cv2
import json
import math
import rospy
from std_msgs.msg import String


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

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('measure', anonymous=True)
    rate = rospy.Rate(20) # 20hz
    while not rospy.is_shutdown():
        intr, depth_intrin, rgb, depth, aligned_depth_frame = get_aligned_images() 
        
        img2 = rgb.copy()
        keypoints1 = orb.detect(img1, None)
        keypoints1, des1 = orb.compute(img1, keypoints1)
        print("keypoints1", keypoints1[0].pt, keypoints1[1].pt, keypoints1[2].pt, keypoints1[3].pt, keypoints1[4].pt, keypoints1[5].pt)
        
        keypoints2 = orb.detect(img2, None)
        keypoints2, des2 = orb.compute(img2, keypoints2)
        # des1 = np.float32(des1)
        # des2 = np.float32(des2)
        flann = cv2.FlannBasedMatcher(indexParams, searchParams)
        matches = flann.knnMatch(des1, des2, k=2)
        matchesMask = [[1, 0] for i in range(len(matches))]
        draw_params = dict(matchColor=(0, 255, 0),
                                singlePointColor=(255, 0, 0),
                                matchesMask=matchesMask,
                                flags=0)
        img3 = cv2.drawMatchesKnn(img1, keypoints1, img2, keypoints2, matches, None, **draw_params)

        for i in range(len(keypoints1)):
            cv2.circle(img3, (int(keypoints1[i].pt[0]), int(keypoints1[i].pt[1])), 2, (0, 0, 255), -1)
        
        
        print("keypoints1 size: ", len(keypoints1))
        print("keypoints2 size: ", len(keypoints2))
        print("match size: ",len(matches))
        cv2.imshow('img3', img3)

        print("============")
        print(aligned_depth_frame)
        x1 = 150  
        y1 = 240
        x2 = 450
        y2 = 240
        dis1 = aligned_depth_frame.get_distance(x1, y1)  
        dis2 = aligned_depth_frame.get_distance(x2, y2)
        #print("dis1: ", dis1)
        #print("dis2: ", dis2)
        camera_coordinate1 = rs.rs2_deproject_pixel_to_point(depth_intrin, [x1, y1], dis1) 
        camera_coordinate2 = rs.rs2_deproject_pixel_to_point(depth_intrin, [x2, y2], dis2)
        #print(camera_coordinate1)
        #print(camera_coordinate2)
        distance = math.sqrt(math.pow(camera_coordinate1[0] - camera_coordinate2[0], 2) + math.pow(camera_coordinate1[1] - camera_coordinate2[1], 2) + math.pow(camera_coordinate1[2] - camera_coordinate2[2], 2))
        print("two point distance: ", distance)
        cv2.circle(rgb, (x1, y1), 4, (0, 0, 255), -1)  
        cv2.circle(rgb, (x2, y2), 4, (0, 0, 255), -1)
        cv2.imshow('RGB image',rgb)  
        key = cv2.waitKey(1)

        rate.sleep()

if __name__ == '__main__':
    img1 = cv2.imread('/home/zff/code/data/model.png')
    orb = cv2.ORB_create()
    print("success!")
    # FLANN_INDEX_KDTREE = 1
    # indexParams = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
    # searchParams = dict(checks=50)
    FLANN_INDEX_LSH = 6
    indexParams = dict(algorithm = FLANN_INDEX_LSH, table_number = 6, key_size = 12, multi_probe_level = 1)
    searchParams = dict(checks = 200)
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
