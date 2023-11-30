; Auto-generated. Do not edit!


(cl:in-package visual_servo-msg)


;//! \htmlinclude joint_positon.msg.html

(cl:defclass <joint_positon> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (shoulder_pan_joint
    :reader shoulder_pan_joint
    :initarg :shoulder_pan_joint
    :type cl:float
    :initform 0.0)
   (shoulder_lift_joint
    :reader shoulder_lift_joint
    :initarg :shoulder_lift_joint
    :type cl:float
    :initform 0.0)
   (elbow_joint
    :reader elbow_joint
    :initarg :elbow_joint
    :type cl:float
    :initform 0.0)
   (wrist_1_joint
    :reader wrist_1_joint
    :initarg :wrist_1_joint
    :type cl:float
    :initform 0.0)
   (wrist_2_joint
    :reader wrist_2_joint
    :initarg :wrist_2_joint
    :type cl:float
    :initform 0.0)
   (wrist_3_joint
    :reader wrist_3_joint
    :initarg :wrist_3_joint
    :type cl:float
    :initform 0.0))
)

(cl:defclass joint_positon (<joint_positon>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <joint_positon>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'joint_positon)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_servo-msg:<joint_positon> is deprecated: use visual_servo-msg:joint_positon instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <joint_positon>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:header-val is deprecated.  Use visual_servo-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'shoulder_pan_joint-val :lambda-list '(m))
(cl:defmethod shoulder_pan_joint-val ((m <joint_positon>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:shoulder_pan_joint-val is deprecated.  Use visual_servo-msg:shoulder_pan_joint instead.")
  (shoulder_pan_joint m))

(cl:ensure-generic-function 'shoulder_lift_joint-val :lambda-list '(m))
(cl:defmethod shoulder_lift_joint-val ((m <joint_positon>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:shoulder_lift_joint-val is deprecated.  Use visual_servo-msg:shoulder_lift_joint instead.")
  (shoulder_lift_joint m))

(cl:ensure-generic-function 'elbow_joint-val :lambda-list '(m))
(cl:defmethod elbow_joint-val ((m <joint_positon>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:elbow_joint-val is deprecated.  Use visual_servo-msg:elbow_joint instead.")
  (elbow_joint m))

(cl:ensure-generic-function 'wrist_1_joint-val :lambda-list '(m))
(cl:defmethod wrist_1_joint-val ((m <joint_positon>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:wrist_1_joint-val is deprecated.  Use visual_servo-msg:wrist_1_joint instead.")
  (wrist_1_joint m))

(cl:ensure-generic-function 'wrist_2_joint-val :lambda-list '(m))
(cl:defmethod wrist_2_joint-val ((m <joint_positon>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:wrist_2_joint-val is deprecated.  Use visual_servo-msg:wrist_2_joint instead.")
  (wrist_2_joint m))

(cl:ensure-generic-function 'wrist_3_joint-val :lambda-list '(m))
(cl:defmethod wrist_3_joint-val ((m <joint_positon>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:wrist_3_joint-val is deprecated.  Use visual_servo-msg:wrist_3_joint instead.")
  (wrist_3_joint m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <joint_positon>) ostream)
  "Serializes a message object of type '<joint_positon>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'shoulder_pan_joint))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'shoulder_lift_joint))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'elbow_joint))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wrist_1_joint))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wrist_2_joint))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wrist_3_joint))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <joint_positon>) istream)
  "Deserializes a message object of type '<joint_positon>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'shoulder_pan_joint) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'shoulder_lift_joint) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'elbow_joint) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wrist_1_joint) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wrist_2_joint) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wrist_3_joint) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<joint_positon>)))
  "Returns string type for a message object of type '<joint_positon>"
  "visual_servo/joint_positon")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'joint_positon)))
  "Returns string type for a message object of type 'joint_positon"
  "visual_servo/joint_positon")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<joint_positon>)))
  "Returns md5sum for a message object of type '<joint_positon>"
  "a82fc01b03f66381c43297a78b5259f1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'joint_positon)))
  "Returns md5sum for a message object of type 'joint_positon"
  "a82fc01b03f66381c43297a78b5259f1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<joint_positon>)))
  "Returns full string definition for message of type '<joint_positon>"
  (cl:format cl:nil "std_msgs/Header header~%float32 shoulder_pan_joint~%float32 shoulder_lift_joint~%float32 elbow_joint~%float32 wrist_1_joint~%float32 wrist_2_joint~%float32 wrist_3_joint~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'joint_positon)))
  "Returns full string definition for message of type 'joint_positon"
  (cl:format cl:nil "std_msgs/Header header~%float32 shoulder_pan_joint~%float32 shoulder_lift_joint~%float32 elbow_joint~%float32 wrist_1_joint~%float32 wrist_2_joint~%float32 wrist_3_joint~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <joint_positon>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <joint_positon>))
  "Converts a ROS message object to a list"
  (cl:list 'joint_positon
    (cl:cons ':header (header msg))
    (cl:cons ':shoulder_pan_joint (shoulder_pan_joint msg))
    (cl:cons ':shoulder_lift_joint (shoulder_lift_joint msg))
    (cl:cons ':elbow_joint (elbow_joint msg))
    (cl:cons ':wrist_1_joint (wrist_1_joint msg))
    (cl:cons ':wrist_2_joint (wrist_2_joint msg))
    (cl:cons ':wrist_3_joint (wrist_3_joint msg))
))
