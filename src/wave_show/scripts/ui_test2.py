#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import sys
sys.path.append("/home/wuyou/BCI_ROS/src/wave_show/ui")

from PySide2.QtWidgets import QApplication, QWidget
from show_test import Ui_Form

app = QApplication([])
widget = QWidget()
ui = Ui_Form()
ui.setupUi(widget)
widget.show()
app.exec_()

