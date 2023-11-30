# online_analysis

本文档用于介绍 online_analysis 功能包中各个文件夹及其包含文件。本功能包内包含四个文件夹:src, scripts, launch, include

## src

在 src 文件夹中,存放 *.cpp 文件,包含节点运行文件与类的定义。

`datareceive.cpp`:链接 Curry8/Curry8 仿真器 的节点,命令行输入`rosrun online_analysis datareceive`运行。该节点只是为了创建一个 ROS 节点,并无 publisher 与 subscriber

`rnetstreamingreceiver.cpp`:根据 Curry8 自带例程修改纯C++类,是与 Curry8/Curry8 仿真器 链接的核心。该类实现了与 Curry8 的 tcp/ip 通信,获取 Curry8 发送的数据包,并发送给其他节点。发布数据涉及到的 publisher 在该类中定义,目前有采样频率、数据包、通道标签的 publisher

`test_talker.cpp`:发布节点(测试)。在该节点中定义了一个最基本的发布节点,需要在 CMakeLists.txt 文件中进行如下配置(文件中已配置):

- `add_executable(test_talker src/test_talker.cpp)`
- `target_link_libraries(test_talker ${catkin_LIBRARIES})`

`test_listener.py`:订阅节点(测试)。在该节点中定义了一个最基本的订阅节点,需要在 CMakeLists.txt 文件中进行如下配置(文件中已配置):

- `add_executable(test_listener src/test_listener.cpp)`
- `target_link_libraries(test_listener ${catkin_LIBRARIES})`

## include

在 include 文件夹中,存放 *.h 文件,包含数据结构体头文件与类的声明。

`Packets.h`:定义了各种数据结构体,用于存放 Curry8 发送的数据

`rnetstreamingreceiver.h`:是`rnetstreamingreceiver.cpp`对应的头文件,包含了类的所有声明。

## scripts

在 scripts 文件夹中,存放 *.py 文件,包含自动发布eeg数据、手动发布eeg数据、读取键盘输入、自定义函数、在线分析、发布节点(测试)、订阅节点(测试)

`eeg_pub_auto.py`:读取了离线脑电数据,并将其切分成固定大小的数据包(35*512),发送给在线分析节点`onlineanalysis.py`

`eeg_pub_manual.py`:读取了离线脑电数据,并根据接收到的键盘输入,选择对应频率的数据包,将其切分成固定大小的数据包(35*512),发送给在线分析节点`onlineanalysis.py`。当键盘输入为1~9时,对应频率为9Hz~17Hz；当键盘输入为0时,生成高斯噪声信号

`key_read.py`:该文件定义了一个发布者,该发布者将用户的键盘输入发送给`eeg_pub_manual.py`以实现对发送数据包的控制。

`my_function.py`:该文件定义了三个函数。

- filterbank:生成滤波器组,并将滤波完成的信号返回
- find:用于查找数组中满足条件结果的个数
- sincosref:用于生成正弦余弦参考信号

`onlineanalysis.py`:在线分析节点。将接收到的数据包进行信号处理,并发布处理后的结果,以此控制外设。

`test_pub.py`:发布节点(测试)。在该节点中定义了一个最基本的发布节点,需要在 CMakeLists.txt 文件中进行如下配置(文件中已配置):

- 在 catkin_install_python 中添加该文件的路径:scripts/test_pub.py

`test_sub.py`:订阅节点(测试)。在该节点中定义了一个最基本的订阅节点,需要在 CMakeLists.txt 文件中进行如下配置(文件中已配置):

- 在 catkin_install_python 中添加该文件的路径:scripts/test_sub.py

## launch

在 launch 文件夹中,存放 *.launch 文件,用于配置多节点启动的控制。目前没有包含任何文件。
