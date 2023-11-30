# Install script for directory: /home/sd/BCI_arm_cam_grip/src/visp_ros

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/sd/BCI_arm_cam_grip/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visp_ros/msg" TYPE FILE FILES
    "/home/sd/BCI_arm_cam_grip/src/visp_ros/msg/BlobTracker.msg"
    "/home/sd/BCI_arm_cam_grip/src/visp_ros/msg/ImagePoint.msg"
    "/home/sd/BCI_arm_cam_grip/src/visp_ros/msg/PoseStampedStatus.msg"
    "/home/sd/BCI_arm_cam_grip/src/visp_ros/msg/ProjectedPoint.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visp_ros/cmake" TYPE FILE FILES "/home/sd/BCI_arm_cam_grip/build/visp_ros/catkin_generated/installspace/visp_ros-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/sd/BCI_arm_cam_grip/devel/include/visp_ros")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/sd/BCI_arm_cam_grip/devel/share/roseus/ros/visp_ros")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/sd/BCI_arm_cam_grip/devel/share/common-lisp/ros/visp_ros")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/sd/BCI_arm_cam_grip/devel/share/gennodejs/ros/visp_ros")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/sd/BCI_arm_cam_grip/devel/lib/python3/dist-packages/visp_ros")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/sd/BCI_arm_cam_grip/devel/lib/python3/dist-packages/visp_ros")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/sd/BCI_arm_cam_grip/build/visp_ros/catkin_generated/installspace/visp_ros.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visp_ros/cmake" TYPE FILE FILES "/home/sd/BCI_arm_cam_grip/build/visp_ros/catkin_generated/installspace/visp_ros-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visp_ros/cmake" TYPE FILE FILES
    "/home/sd/BCI_arm_cam_grip/build/visp_ros/catkin_generated/installspace/visp_rosConfig.cmake"
    "/home/sd/BCI_arm_cam_grip/build/visp_ros/catkin_generated/installspace/visp_rosConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visp_ros" TYPE FILE FILES "/home/sd/BCI_arm_cam_grip/src/visp_ros/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-ibvs-apriltag" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-ibvs-apriltag")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-ibvs-apriltag"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/tutorial-franka-coppeliasim-ibvs-apriltag")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-ibvs-apriltag" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-ibvs-apriltag")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-ibvs-apriltag"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-ibvs-apriltag")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-pbvs-apriltag" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-pbvs-apriltag")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-pbvs-apriltag"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/tutorial-franka-coppeliasim-pbvs-apriltag")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-pbvs-apriltag" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-pbvs-apriltag")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-pbvs-apriltag"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-pbvs-apriltag")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-joint-impedance-control" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-joint-impedance-control")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-joint-impedance-control"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/tutorial-franka-coppeliasim-joint-impedance-control")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-joint-impedance-control" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-joint-impedance-control")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-joint-impedance-control"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/tutorial-franka-coppeliasim-joint-impedance-control")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/sd/BCI_arm_cam_grip/devel/lib/libvisp_ros.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros.so"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_afma6_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_afma6_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_afma6_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/visp_ros_afma6_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_afma6_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_afma6_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_afma6_node"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_afma6_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_biclops_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_biclops_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_biclops_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/visp_ros_biclops_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_biclops_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_biclops_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_biclops_node"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_biclops_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_blob_tracker_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_blob_tracker_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_blob_tracker_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/visp_ros_blob_tracker_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_blob_tracker_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_blob_tracker_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_blob_tracker_node"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_blob_tracker_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_pbvs_blob_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_pbvs_blob_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_pbvs_blob_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/visp_ros_pbvs_blob_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_pbvs_blob_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_pbvs_blob_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_pbvs_blob_node"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_pbvs_blob_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper650_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper650_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper650_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/visp_ros_viper650_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper650_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper650_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper650_node"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper650_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper850_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper850_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper850_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/visp_ros_viper850_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper850_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper850_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper850_node"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_viper850_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_bebop2_visual_servo_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_bebop2_visual_servo_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_bebop2_visual_servo_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visp_ros" TYPE EXECUTABLE FILES "/home/sd/BCI_arm_cam_grip/devel/lib/visp_ros/visp_ros_bebop2_visual_servo_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_bebop2_visual_servo_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_bebop2_visual_servo_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_bebop2_visual_servo_node"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visp_ros/visp_ros_bebop2_visual_servo_node")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros_bebop2_visual_servo_nodelet.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros_bebop2_visual_servo_nodelet.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros_bebop2_visual_servo_nodelet.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/sd/BCI_arm_cam_grip/devel/lib/libvisp_ros_bebop2_visual_servo_nodelet.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros_bebop2_visual_servo_nodelet.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros_bebop2_visual_servo_nodelet.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros_bebop2_visual_servo_nodelet.so"
         OLD_RPATH "/opt/ros/noetic/lib:/home/sd/BCI_arm_cam_grip/devel/lib:/opt/ros/noetic/lib/x86_64-linux-gnu:/usr/local/lib:/usr/lib/gcc/x86_64-linux-gnu/8:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libvisp_ros_bebop2_visual_servo_nodelet.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visp_ros" TYPE FILE FILES "/home/sd/BCI_arm_cam_grip/src/visp_ros/nodelet_plugins.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/visp_ros" TYPE DIRECTORY FILES "/home/sd/BCI_arm_cam_grip/src/visp_ros/include/visp_ros/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/\\.svn$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visp_ros/launch" TYPE DIRECTORY FILES "/home/sd/BCI_arm_cam_grip/src/visp_ros/launch/")
endif()

