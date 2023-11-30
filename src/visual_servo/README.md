# visual_servo功能包  
## 功能
对相机进行手眼标定    
## 需要配置visp、visp-ros、vision-visp
参考 <https://github.com/lagadic/visp_ros/tree/noetic> 
### 配置vision-visp
#### 只需要下载功能包，不需要单独编译  
`$ cd ~/code/BCI_ws/src`  
`$ source /opt/ros/noetic/setup.bash`  
`$ git clone https://github.com/lagadic/vision_visp.git -b $ROS_DISTRO`  
*这一步可以直接下载，不用从github上clone*  
### 配置visp
#### 安装依赖
`$ sudo apt-get install libopencv-dev libx11-dev liblapack-dev libeigen3-dev libv4l-dev  
libzbar-dev libpthread-stubs0-dev libjpeg-dev libpng-dev`  
对visp更多了解可以参考 <https://visp-doc.inria.fr/doxygen/visp-daily/tutorial-install-ubuntu.html>
#### 单独创建工作空间 _visp-ws_  
`$ cd visp-ws`  
`$ git clone https://github.com/lagadic/visp.git`  
`$ mkdir visp-build-ros`  
`cd visp-build-ros`  
`$ cmake -DCMAKE_INSTALL_PREFIX=/opt/ros/$ROS_DISTRO ../visp`  
`$ make -j4`  
`sudo make install`  
#### 获取visp-ros功能包源码
`$ git clone https://github.com/lagadic/visp_ros.git`  
#### 编译visp-ros功能包
`$ cd ~/code/BCI_ws`  
`$ catkin_make -DCMAKE_BUILD_TYPE=Release --pkg visp_ros`  
#### 此时编译BCI_ws即可将visual_servo功能包成功编译
`$ catkin_make`  
## 节点说明
### ur_getdata.cpp
用来读取UR5机械臂当前位姿信息（六个关节角）  
### hand_eye_arm_control.cpp
将提前获取到的七个机械臂位姿信息输入宏定义处，将控制机械臂按序运动至这几个姿态，并获取各个位姿下相机中的图片
### hand_eye_arm_calculate.cpp
用来根据各个位姿下机械臂上相机图片计算出手眼关系齐次变换矩阵  
## 节点运行注意事项
* 将机械臂手动移动到某一位姿后，运行 _ur_getdata.cpp_ 节点，将终端中输出的信息记录
* 开两个终端，先运行 _hand_eye_arm_calculate.cpp_ 节点等待接受数据，再运行 _hand_eye_arm_control.cpp_ 节点
* 要将和ur_rtde相关的头文件引用移到Eigen/Geometry相关文件引用之后，否则会编译错误！