##############################################################################
# CMake
##############################################################################
# 设置cmake的最低版本
cmake_minimum_required(VERSION 3.0.2)
# 设置项目名称
project(qt_ros)
# 设置C++版本
set(CMAKE_CXX_STANDARD 17)
# add
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# 设置优先路径
set(QT_PATH "/home/sd/Qt5.9.9/5.9.9/gcc_64/lib/cmake" CACHE PATH "qt5 cmake dir")
list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})

SET(FILT_SRCS
  src/chebyshev_iir.cpp
  src/find_roots.cpp
  src/iir_coeff.cpp
  src/design_iir.cpp
  src/FFT.cpp
)
add_library(spuce ${FILT_SRCS})

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS roscpp)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
# add
# find_package(Qt5 REQUIRED Core Widgets Network)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Network)
find_package(Qt5Charts)

# set(QT_INCLUDE_DIRS ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})
include_directories(
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5Network_INCLUDE_DIRS}
  ${Qt5Charts_INCLUDE_DIRS}
)

# set(QT_LIBRARIES Qt5::Widgets Qt5::Network)
list(APPEND QT_LIBS
  ${Qt5Core_LIBRARIES}
  ${Qt5Gui_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
  ${Qt5Network_LIBRARIES}
  ${Qt5Charts_LIBRARIES}
)

# add_definitions(${Qt5Gui_DEFINITIONS} ${Qt5Widgets_DEFINITIONS} ${Qt5Network_DEFINITIONS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything. 
catkin_package()


##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically 
# included via the dependency call in package.xml
# remove
# rosbuild_prepare_qt4(QtCore QtGui) # Add the appropriate components to the component list here

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/qt_ros/*.hpp)

# change QT4 to QT5
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})
# QT4_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
# QT4_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
# QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################

#add_library(NetStreamingReceiver
#   include/qt_ros/NetStreamingReceiver.h
#   src/NetStreamingReceiver.cpp
#)
#target_link_libraries(NetStreamingReceiver ${QT_LIBS} ${catkin_LIBRARIES})

#add_subdirectory(kfr)

add_library(QNetStreamingReceiver
  include/qt_ros/qnetstreamingreceiver.hpp
  src/qnetstreamingreceiver.cpp
)
target_link_libraries(QNetStreamingReceiver ${QT_LIBS} ${catkin_LIBRARIES})

add_executable(qt_ros ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(qt_ros ${QT_LIBS} ${catkin_LIBRARIES})
install(TARGETS qt_ros RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

