# wave_show

本文档用于介绍 wave_show 功能包中各个文件夹及其包含文件。本功能包内包含两个文件夹:scripts, ui

## scripts

在 scripts 文件夹中，存放 *.py 文件，包含节点运行文件。

`wave_show.py`:该文件调用设计好的界面`ui_waveshow.ui`，定义了多个信号与槽的连接，定义了多个订阅节点用于获取采样频率、通道标签、数据包，并实现了信号处理功能。在命令行中输入`rosrun wave_show wave_show.py`运行

## ui

在 ui 文件夹中，存放 *.ui 文件

`ui_waveshow.ui`:该文件为使用 qt designer 设计的可视化界面，实现了各模块的布局。

## Python Qt 结合

### Python 图形界面开发的几种方案

程序的用户交互界面，英文成为 UI(user interface)。当一个应用的 UI 比较复杂时，命令行方式就不便于用户的使用了，这时候我们需要图形界面。如果用 Python 进行跨平台的图形界面程序开发，主要有以下三种选择：

- tkinter
  
  基于 Tk 的 Python 库，这是 Python 官方采用的标准库，优点是作为 Python 标准库、稳定、发布程序较小，缺点是控件相对较少。

- wxPython
  
  基于 wxWidgets 的 Python 库，优点是控件比较丰富，缺点是稳定性相对差点、文档少、用户少。

- Pyside2/Pyside6 PyQt5/PyQt6
  
  基于 Qt 的 Python 库，优点是控件比较丰富、跨平台体验好、文档完善、用户多，缺点是库比较大，发布出来的程序比较大。

在此处，我们采用的是 Pyside2 进行界面的开发。安装 Pyside2 很简单，在命令行中执行`pip install pyside2`即可安装。

### 图形界面的两种调用方式

Pyside2 安装成功后，在命令行中输入`designer`即可打开设计器，进行界面布局设计。布局完成后，保存为 *.ui 文件。在此，我们有两种方式可以使用这个 ui 文件。

- 方式一：直接调用 ui 文件(参考 ui_test1.py)
  
  直接调用 ui 文件也有两种方法：直接用 QUiLoader 打开，用 QFile 间接打开。在此处，我们使用直接用 QUiLoader 打开的方式。

- 方式二：将 ui 文件转换为 python 代码，然后使用生成的界面(参考 ui_test2.py)
  
  将 ui 文件转换为 python 代码，需要在终端中输入`pyside2-uic test.ui -o test.py`。这个命令的一般形式为`pyside2-uic input.ui -o output.py`，其中`pyside2-uic`为安装 Pyside2 时自动安装的工具；`input.ui`为需要转换的 ui 文件名称，也即输入文件的名称；`-o`表示输出命令；`output.py`为转换后的 python 文件名称，也即输出文件的名称。

  在调用 python 文件时，我们使用`from package import module`的方式，其中`package`处为生成的 python 文件名称，`module`为该文件中类的名称。
  