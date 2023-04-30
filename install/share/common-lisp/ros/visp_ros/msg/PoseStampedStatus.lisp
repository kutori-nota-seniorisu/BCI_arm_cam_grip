; Auto-generated. Do not edit!


(cl:in-package visp_ros-msg)


;//! \htmlinclude PoseStampedStatus.msg.html

(cl:defclass <PoseStampedStatus> (roslisp-msg-protocol:ros-message)
  ((status
    :reader status
    :initarg :status
    :type cl:fixnum
    :initform 0)
   (pose_stamped
    :reader pose_stamped
    :initarg :pose_stamped
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped)))
)

(cl:defclass PoseStampedStatus (<PoseStampedStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PoseStampedStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PoseStampedStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visp_ros-msg:<PoseStampedStatus> is deprecated: use visp_ros-msg:PoseStampedStatus instead.")))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <PoseStampedStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visp_ros-msg:status-val is deprecated.  Use visp_ros-msg:status instead.")
  (status m))

(cl:ensure-generic-function 'pose_stamped-val :lambda-list '(m))
(cl:defmethod pose_stamped-val ((m <PoseStampedStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visp_ros-msg:pose_stamped-val is deprecated.  Use visp_ros-msg:pose_stamped instead.")
  (pose_stamped m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PoseStampedStatus>) ostream)
  "Serializes a message object of type '<PoseStampedStatus>"
  (cl:let* ((signed (cl:slot-value msg 'status)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose_stamped) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PoseStampedStatus>) istream)
  "Deserializes a message object of type '<PoseStampedStatus>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'status) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose_stamped) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PoseStampedStatus>)))
  "Returns string type for a message object of type '<PoseStampedStatus>"
  "visp_ros/PoseStampedStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseStampedStatus)))
  "Returns string type for a message object of type 'PoseStampedStatus"
  "visp_ros/PoseStampedStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PoseStampedStatus>)))
  "Returns md5sum for a message object of type '<PoseStampedStatus>"
  "71ae8a9e7c5c6a036498a62872a0dbc4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PoseStampedStatus)))
  "Returns md5sum for a message object of type 'PoseStampedStatus"
  "71ae8a9e7c5c6a036498a62872a0dbc4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PoseStampedStatus>)))
  "Returns full string definition for message of type '<PoseStampedStatus>"
  (cl:format cl:nil "int8 status~%geometry_msgs/PoseStamped pose_stamped~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PoseStampedStatus)))
  "Returns full string definition for message of type 'PoseStampedStatus"
  (cl:format cl:nil "int8 status~%geometry_msgs/PoseStamped pose_stamped~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PoseStampedStatus>))
  (cl:+ 0
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose_stamped))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PoseStampedStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'PoseStampedStatus
    (cl:cons ':status (status msg))
    (cl:cons ':pose_stamped (pose_stamped msg))
))
