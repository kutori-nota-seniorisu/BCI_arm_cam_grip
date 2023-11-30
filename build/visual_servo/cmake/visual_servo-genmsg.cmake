# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "visual_servo: 6 messages, 0 services")

set(MSG_I_FLAGS "-Ivisual_servo:/home/sd/BCI_arm_cam_grip/src/visual_servo/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(visual_servo_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg" NAME_WE)
add_custom_target(_visual_servo_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_servo" "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg" NAME_WE)
add_custom_target(_visual_servo_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_servo" "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg" NAME_WE)
add_custom_target(_visual_servo_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_servo" "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg" NAME_WE)
add_custom_target(_visual_servo_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_servo" "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg" NAME_WE)
add_custom_target(_visual_servo_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_servo" "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg" NAME_WE)
add_custom_target(_visual_servo_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visual_servo" "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo
)
_generate_msg_cpp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo
)
_generate_msg_cpp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo
)
_generate_msg_cpp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo
)
_generate_msg_cpp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo
)
_generate_msg_cpp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo
)

### Generating Services

### Generating Module File
_generate_module_cpp(visual_servo
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(visual_servo_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(visual_servo_generate_messages visual_servo_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_cpp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_cpp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_cpp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_cpp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_cpp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_cpp _visual_servo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_servo_gencpp)
add_dependencies(visual_servo_gencpp visual_servo_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_servo_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo
)
_generate_msg_eus(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo
)
_generate_msg_eus(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo
)
_generate_msg_eus(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo
)
_generate_msg_eus(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo
)
_generate_msg_eus(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo
)

### Generating Services

### Generating Module File
_generate_module_eus(visual_servo
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(visual_servo_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(visual_servo_generate_messages visual_servo_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_eus _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_eus _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_eus _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_eus _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_eus _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_eus _visual_servo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_servo_geneus)
add_dependencies(visual_servo_geneus visual_servo_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_servo_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo
)
_generate_msg_lisp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo
)
_generate_msg_lisp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo
)
_generate_msg_lisp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo
)
_generate_msg_lisp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo
)
_generate_msg_lisp(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo
)

### Generating Services

### Generating Module File
_generate_module_lisp(visual_servo
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(visual_servo_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(visual_servo_generate_messages visual_servo_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_lisp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_lisp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_lisp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_lisp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_lisp _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_lisp _visual_servo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_servo_genlisp)
add_dependencies(visual_servo_genlisp visual_servo_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_servo_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo
)
_generate_msg_nodejs(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo
)
_generate_msg_nodejs(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo
)
_generate_msg_nodejs(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo
)
_generate_msg_nodejs(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo
)
_generate_msg_nodejs(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo
)

### Generating Services

### Generating Module File
_generate_module_nodejs(visual_servo
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(visual_servo_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(visual_servo_generate_messages visual_servo_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_nodejs _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_nodejs _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_nodejs _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_nodejs _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_nodejs _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_nodejs _visual_servo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_servo_gennodejs)
add_dependencies(visual_servo_gennodejs visual_servo_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_servo_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo
)
_generate_msg_py(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo
)
_generate_msg_py(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo
)
_generate_msg_py(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo
)
_generate_msg_py(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo
)
_generate_msg_py(visual_servo
  "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo
)

### Generating Services

### Generating Module File
_generate_module_py(visual_servo
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(visual_servo_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(visual_servo_generate_messages visual_servo_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle1.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_py _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/pbvs_circles.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_py _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/circle.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_py _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/joint_positon.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_py _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/toolposeChange.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_py _visual_servo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sd/BCI_arm_cam_grip/src/visual_servo/msg/RobotRelative.msg" NAME_WE)
add_dependencies(visual_servo_generate_messages_py _visual_servo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visual_servo_genpy)
add_dependencies(visual_servo_genpy visual_servo_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visual_servo_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visual_servo
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(visual_servo_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/visual_servo
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(visual_servo_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visual_servo
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(visual_servo_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/visual_servo
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(visual_servo_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visual_servo
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(visual_servo_generate_messages_py std_msgs_generate_messages_py)
endif()
