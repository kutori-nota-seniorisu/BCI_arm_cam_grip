#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/sd/BCI_arm_cam_grip/src/robotiq-noetic-devel/robotiq_3f_gripper_control"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/sd/BCI_arm_cam_grip/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/sd/BCI_arm_cam_grip/install/lib/python3/dist-packages:/home/sd/BCI_arm_cam_grip/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/sd/BCI_arm_cam_grip/build" \
    "/usr/bin/python3" \
    "/home/sd/BCI_arm_cam_grip/src/robotiq-noetic-devel/robotiq_3f_gripper_control/setup.py" \
     \
    build --build-base "/home/sd/BCI_arm_cam_grip/build/robotiq-noetic-devel/robotiq_3f_gripper_control" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/sd/BCI_arm_cam_grip/install" --install-scripts="/home/sd/BCI_arm_cam_grip/install/bin"
