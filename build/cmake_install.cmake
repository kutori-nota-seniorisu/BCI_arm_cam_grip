# Install script for directory: /home/sd/BCI_arm_cam_grip/src

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
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sd/BCI_arm_cam_grip/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sd/BCI_arm_cam_grip/install" TYPE PROGRAM FILES "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/_setup_util.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sd/BCI_arm_cam_grip/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sd/BCI_arm_cam_grip/install" TYPE PROGRAM FILES "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/env.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sd/BCI_arm_cam_grip/install/setup.bash;/home/sd/BCI_arm_cam_grip/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sd/BCI_arm_cam_grip/install" TYPE FILE FILES
    "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/setup.bash"
    "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/local_setup.bash"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sd/BCI_arm_cam_grip/install/setup.sh;/home/sd/BCI_arm_cam_grip/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sd/BCI_arm_cam_grip/install" TYPE FILE FILES
    "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/setup.sh"
    "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/local_setup.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sd/BCI_arm_cam_grip/install/setup.zsh;/home/sd/BCI_arm_cam_grip/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sd/BCI_arm_cam_grip/install" TYPE FILE FILES
    "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/setup.zsh"
    "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/sd/BCI_arm_cam_grip/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/sd/BCI_arm_cam_grip/install" TYPE FILE FILES "/home/sd/BCI_arm_cam_grip/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/sd/BCI_arm_cam_grip/build/gtest/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_2f_140_gripper_visualization/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_2f_85_gripper_visualization/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_2f_c2_gripper_visualization/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_3f_gripper_articulated_gazebo/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_3f_gripper_articulated_msgs/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/vision_visp/vision_visp/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/wave_show/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/online_analysis/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_ethercat/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_2f_gripper_control/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_ft_sensor/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_modbus_rtu/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_modbus_tcp/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_2f_gripper_action_server/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_3f_gripper_control/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_3f_gripper_joint_state_publisher/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_3f_gripper_articulated_gazebo_plugins/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_3f_gripper_visualization/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_3f_rviz/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/vision_visp/visp_bridge/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/vision_visp/visp_camera_calibration/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/vision_visp/visp_hand2eye_calibration/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/visp_ros/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/vision_visp/visp_tracker/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/vision_visp/visp_auto_tracker/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/visual_servo/cmake_install.cmake")
  include("/home/sd/BCI_arm_cam_grip/build/bci_grip/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/sd/BCI_arm_cam_grip/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
