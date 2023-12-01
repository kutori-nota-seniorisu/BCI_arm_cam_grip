# BCI_ROS

本手册旨在详细解释本工作空间，并介绍各功能包的功能与使用。此工作空间内包含三个功能包: online_analysis, ptb_show, wave_show。其中 online_analysis 功能包用于分析脑电信号数据，并发布机械臂控制指令； ptb_show 功能包用于显示刺激界面； wave_show 功能包用于显示脑电信号的可视化。

## 2023.06.12

不再使用qt采集脑电信号，将C++ demo代码写成纯ROS C++类

本机ubuntu版本 20.04

pip更新: `python3 -m pip install --upgrade pip`

## 工控机配置指南

ubuntu版本 18.04

ros版本 melodic

Qt版本 5.9.9

## 节点运行方式

### 离线数据手动发布并分析

效果：通过键盘输入0~9来控制离线数据的发布，并将数据发送给分析节点。

1. 运行数据分析的节点：`rosrun online_analysis onlineanalysis.py`
2. 运行离线数据发布的节点：`rosrun online_analysis eeg_pub_manual.py`
3. 运行获取键盘输入的节点：`rosrun online_analysis key_read.py`

### 在线数据获取并分析

效果：采集在线数据（Curry8或仿真器），并将数据发送给分析节点。

1. 运行 Curry8 仿真器/ Curry8
2. 运行连接 Curry8 的数据采集节点：`rosrun online_analysis datareceive`
3. 运行数据分析的节点：`rosrun online_analysis onlineanalysis.py`

### 脑电信号可视化

效果：采集数据后，将数据发送给可视化界面，在界面上绘制波形图，并具有信号滤波功能。

1. 运行可视化界面节点：`rosrun wave_show wave_show.py`
2. 运行 Curry8 仿真器/ Curry8
3. 运行连接 Curry8 的数据采集节点：`rosrun online_analysis datareceive`

## 相机相关

1. 首先运行相机配置launch文件：`roslaunch realsense2_camera rs_aligned_depth.launch`
2. 接着运行数据发送与分析节点：`roslaunch online_analysis ana_simu.launch`
3. 最后运行相机节点：`rosrun bci_grip col_align_depth.cpp`

## ptb 刺激界面

请使用ssvep_ptb_1.py