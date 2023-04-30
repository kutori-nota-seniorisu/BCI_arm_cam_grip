# 功能包文件解释

## basic_filterbank.py
封装了生成滤波器组的函数

## sincos_ref.py
封装了生成参考信号的函数

## eeg_pub.py
发布离线的脑电数据
接收key_read节点发送的键盘输入，以控制发布的数据

## key_read.py
发布通过键盘输入的数据

## onlineanalysis.py
对脑电信号进行分析，可以选择CCA或FBCCA