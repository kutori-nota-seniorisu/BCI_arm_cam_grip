#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
from PySide2.QtWidgets import QApplication
from PySide2.QtUiTools import QUiLoader
from PySide2.QtCore import QFile

app = QApplication([])

loader = QUiLoader()
ui = loader.load("/home/wuyou/BCI_ROS/src/wave_show/ui/show_test.ui")

# 以下这种方法也可以读取 ui 文件并调用
# stats = QFile("/home/wuyou/BCI_ROS/src/wave_show/ui/test.ui")
# stats.open(QFile.ReadOnly)
# stats.close()
# ui = QUiLoader().load(stats)

ui.show()

app.exec_()

