;; Auto-generated. Do not edit!


(when (boundp 'visp_ros::PoseStampedStatus)
  (if (not (find-package "VISP_ROS"))
    (make-package "VISP_ROS"))
  (shadow 'PoseStampedStatus (find-package "VISP_ROS")))
(unless (find-package "VISP_ROS::POSESTAMPEDSTATUS")
  (make-package "VISP_ROS::POSESTAMPEDSTATUS"))

(in-package "ROS")
;;//! \htmlinclude PoseStampedStatus.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass visp_ros::PoseStampedStatus
  :super ros::object
  :slots (_status _pose_stamped ))

(defmethod visp_ros::PoseStampedStatus
  (:init
   (&key
    ((:status __status) 0)
    ((:pose_stamped __pose_stamped) (instance geometry_msgs::PoseStamped :init))
    )
   (send-super :init)
   (setq _status (round __status))
   (setq _pose_stamped __pose_stamped)
   self)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:pose_stamped
   (&rest __pose_stamped)
   (if (keywordp (car __pose_stamped))
       (send* _pose_stamped __pose_stamped)
     (progn
       (if __pose_stamped (setq _pose_stamped (car __pose_stamped)))
       _pose_stamped)))
  (:serialization-length
   ()
   (+
    ;; int8 _status
    1
    ;; geometry_msgs/PoseStamped _pose_stamped
    (send _pose_stamped :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _status
       (write-byte _status s)
     ;; geometry_msgs/PoseStamped _pose_stamped
       (send _pose_stamped :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _status
     (setq _status (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _status 127) (setq _status (- _status 256)))
   ;; geometry_msgs/PoseStamped _pose_stamped
     (send _pose_stamped :deserialize buf ptr-) (incf ptr- (send _pose_stamped :serialization-length))
   ;;
   self)
  )

(setf (get visp_ros::PoseStampedStatus :md5sum-) "71ae8a9e7c5c6a036498a62872a0dbc4")
(setf (get visp_ros::PoseStampedStatus :datatype-) "visp_ros/PoseStampedStatus")
(setf (get visp_ros::PoseStampedStatus :definition-)
      "int8 status
geometry_msgs/PoseStamped pose_stamped

================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

")



(provide :visp_ros/PoseStampedStatus "71ae8a9e7c5c6a036498a62872a0dbc4")


