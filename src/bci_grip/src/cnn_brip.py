#!/usr/bin/env python3

import tensorflow as tf
from grasp_inf import inference
from grasp_det import grasp_to_bbox
import cv2

# 需要根据自己下载的Cornell Grasping Dataset或者其他图片的目录进行修改
# 后面应用到机械臂抓取时需要接收摄像机的实时图像数据
filename = './cornell_grasping_dataset/image/image/pcd0159r.png'

def draw_bbox(img, bbox):
    p1 = (int(float(bbox[0][0]) / 0.35), int(float(bbox[0][1]) / 0.47))
    p2 = (int(float(bbox[1][0]) / 0.35), int(float(bbox[1][1]) / 0.47))
    p3 = (int(float(bbox[2][0]) / 0.35), int(float(bbox[2][1]) / 0.47))
    p4 = (int(float(bbox[3][0]) / 0.35), int(float(bbox[3][1]) / 0.47))

    cv2.line(img, p1, p2, (255, 0, 0))
    cv2.line(img, p2, p3, (0, 0, 255))
    cv2.line(img, p3, p4, (0, 0, 255))
    cv2.line(img, p4, p1, (0, 0, 255))


if __name__ == '__main__':
    init_op = tf.group(tf.global_variables_initializer(), tf.local_variables_initializer())
    sess = tf.Session()
    sess.run(init_op)
    img_raw_data = tf.gfile.FastGFile(filename, 'rb').read()
    img_show = cv2.imread(filename)
    img_data = tf.image.decode_png(img_raw_data)
    img_data = tf.image.convert_image_dtype(img_data, dtype=tf.float32)
    img_reshape = tf.image.resize_images(img_data, [224, 224])
    img_reshape = tf.reshape(img_reshape, shape=[1, 224, 224, 3])
    x_hat, y_hat, tan_hat, w_hat, h_hat = tf.unstack(inference(img_reshape), axis=1)
    bbox_hat = grasp_to_bbox(x_hat, y_hat, tan_hat, h_hat, w_hat)
    dg={}
    lg = ['w1', 'b1', 'w2', 'b2', 'w3', 'b3', 'w4', 'b4', 'w5', 'b5', 'w_fc1', 'b_fc1', 'w_fc2', 'b_fc2', 'w_output', 'b_output']
    for i in lg:
        dg[i] = [v for v in tf.get_collection(tf.GraphKeys.GLOBAL_VARIABLES) if v.name == i+':0'][0]

    saver_g = tf.train.Saver(dg)
    saver_g.restore(sess, './models/grasp/m4/m4.ckpt')
    bbox_model = sess.run(bbox_hat)
    print("x_hat, y_hat, tan_hat, w_hat, h_hat",sess.run(x_hat),sess.run(y_hat),sess.run(tan_hat),sess.run(w_hat),sess.run(h_hat))
    draw_bbox(img_show, bbox_model)
    cv2.imshow('bbox', img_show)
    cv2.waitKey(0)