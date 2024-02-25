# BCI_ROS

本手册旨在详细解释本工作空间，并介绍各功能包的功能与使用。此工作空间内包含三个功能包: online_analysis, ptb_show, wave_show。其中 online_analysis 功能包用于分析脑电信号数据，并发布机械臂控制指令； ptb_show 功能包用于显示刺激界面； wave_show 功能包用于显示脑电信号的可视化。

## 更新日志

### 2023.05.12

ubuntu版本 18.04  
ros版本 melodic  
Qt版本 5.9.9

### 2023.06.12

不再使用qt采集脑电信号，将C++ demo代码写成纯ROS C++类  
本机ubuntu版本 20.04  
pip更新: `python3 -m pip install --upgrade pip`  
工控机重装系统，使用 ubuntu20.04

### 2024.01.22

关于链接的设置，在这里记录一下。  
___一定要断网，一定要关防火墙___  
需要三根水晶线，蓝色线连grael和output口，黑色一根连input口和电脑，黑色一根连工控机和电脑（用拓展坞）。  
grael默认IP地址为169.254.22.159，故从input口连出来的水晶线，需要在电脑上设置IP地址为169.254.22.x，在这里我把IP地址设置为169.254.22.11。  
在CURRY8上点开设置文件，NetStreaming Server的下拉框显示了一个默认IP，以及两个水晶头产生的额外IP。在这里设置连接在拓展坞上的水晶头的IP为169.254.103.214，与直接连接到电脑的水晶头的IP地址产生区别。  
工控机上水晶头对应口的IP地址设置为169.254.103.213，互相需要可以ping通。工控机上datareceive函数里设置的IP地址需要是CURRY8上NetStreaming Server处显示的IP地址，在这里就是169.254.103.214

### 2024.02.25

新增了变量receive_state用于判断能够接收脑电数据。当为true时可以接收，当为false时拒绝接收。  
当分析结果为15Hz时，相机可以传递图像，此时清空脑电数据。  
当分析结果为其他频率时，正常发布该结果。当机械臂节点接收到该结果，并能与预设频率数组匹配，则发布话题，使分析节点停止接收数据，并清空已有数据。当抓取完成后，机械臂节点发布话题，使分析节点能够接收数据。

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