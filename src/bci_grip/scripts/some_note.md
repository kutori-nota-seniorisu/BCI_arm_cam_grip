# 一些记录

## 切记切记切记

没有push！没有push！！没有push！！！
新建分支push！新建分支push！！新建分支push！！！

在终端输入`env`可以查看环境变量，其中PYTHONPATH对应的就是python的路径（废话）

python文件第一行注释，用于指定使用哪个python解释器，其格式为：

```py
#!/usr/bin/env python
```

这句话的意思相当于是，到env环境变量里的PYTHONPATH去查找python解释器的路径，并且调用该路径下的解释器

***切记切记不要在#和!之间加空格！！！！！***

如果将python改为python3，则使用python3运行文件

python文件第二行注释，能够输出中文，其格式为：

```py
# -*- coding: UTF-8 -*-
```

## python3 重新编译 cv_bridge

ubuntu18.04安装的是melodic，包含的cv_bridge是基于python2的。当使用python3作为解释器时，cv_bridge不能正常调用，因而需要重新编译python3的cv_bridge

参考了以下一些文档：

[ROS——基于python3实现opencv图像处理任务](https://zhuanlan.zhihu.com/p/525137856)

[ROS（melodic版本）在python3.6下用cv_bridge把sensor_msgs/Image消息转换为opencv格式的图片](https://blog.csdn.net/weixin_43434136/article/details/112646275?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_title~default-1.control&spm=1001.2101.3001.4242)

```cmd
sudo apt-get install python-catkin-tools python3-dev python3-catkin-pkg-modules python3-numpy python3-yaml ros-melodic-cv-bridge
cd ~
mkdir cv_bridge_ws
cd cv_bridge_ws
catkin init
catkin config -DPYTHON_EXECUTABLE=/usr/bin/python3 -DPYTHON_INCLUDE_DIR=/usr/include/python3.6m -DPYTHON_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.6m.so
catkin config --install
git clone https://github.com/ros-perception/vision_opencv.git src/vision_opencv
apt-cache show ros-melodic-cv-bridge | grep Version
cd src/vision_opencv/
git checkout 1.13.x
cd ../../
catkin build cv_bridge
```

这样就好了。为了不用每次都source，我们把对应的语句写到.bashrc里。不知为什么，写在bashrc里的也没有用，需要每次在终端运行下面的指令。

```bash
source /home/sd/cv_bridge_ws/install/setup.bash --extend
```

编译需要运行的工作空间要这样子！！！（暂时无用）

```cmd
catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3
```

## 致老王

回调函数这样写

```py
def Picture_Callback(msg):
	global Pic
	bridge = CvBridge()
	Pic = bridge.imgmsg_to_cv2(msg, "bgr8")
```

不是这样

```py
def Picture_Callback(msg):
	global Pic
	Pic = CvBridge.imgmsg_to_cv2(msg, "bgr8")
```

这样子也可以

```py
def Picture_Callback(msg):
	global Pic
	Pic = CvBridge().imgmsg_to_cv2(msg, "bgr8")
```

用节点发送两次才能接收到话题，用终端rostopic发送多次也没用？？？

## 牛逼的markdownlint配置

在markdown中写代码块，python用四个空格缩进。这是不能忍受的，所以修改了markdownlint的报错机制。详见文章，不再赘述。

[markdownlint规则详细介绍及自定义参数设置](https://blog.csdn.net/weixin_44149294/article/details/126243402)

[详解markdownlint](https://www.python100.com/html/94538.html)
