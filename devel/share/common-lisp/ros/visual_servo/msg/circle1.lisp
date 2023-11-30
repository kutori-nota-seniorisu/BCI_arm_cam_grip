; Auto-generated. Do not edit!


(cl:in-package visual_servo-msg)


;//! \htmlinclude circle1.msg.html

(cl:defclass <circle1> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (radius
    :reader radius
    :initarg :radius
    :type cl:float
    :initform 0.0)
   (center_x
    :reader center_x
    :initarg :center_x
    :type cl:float
    :initform 0.0)
   (center_y
    :reader center_y
    :initarg :center_y
    :type cl:float
    :initform 0.0))
)

(cl:defclass circle1 (<circle1>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <circle1>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'circle1)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_servo-msg:<circle1> is deprecated: use visual_servo-msg:circle1 instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <circle1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:header-val is deprecated.  Use visual_servo-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <circle1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:name-val is deprecated.  Use visual_servo-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'radius-val :lambda-list '(m))
(cl:defmethod radius-val ((m <circle1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:radius-val is deprecated.  Use visual_servo-msg:radius instead.")
  (radius m))

(cl:ensure-generic-function 'center_x-val :lambda-list '(m))
(cl:defmethod center_x-val ((m <circle1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:center_x-val is deprecated.  Use visual_servo-msg:center_x instead.")
  (center_x m))

(cl:ensure-generic-function 'center_y-val :lambda-list '(m))
(cl:defmethod center_y-val ((m <circle1>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:center_y-val is deprecated.  Use visual_servo-msg:center_y instead.")
  (center_y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <circle1>) ostream)
  "Serializes a message object of type '<circle1>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radius))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'center_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'center_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <circle1>) istream)
  "Deserializes a message object of type '<circle1>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radius) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'center_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'center_y) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<circle1>)))
  "Returns string type for a message object of type '<circle1>"
  "visual_servo/circle1")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'circle1)))
  "Returns string type for a message object of type 'circle1"
  "visual_servo/circle1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<circle1>)))
  "Returns md5sum for a message object of type '<circle1>"
  "ad34fcda4d5e7bd900535ed16cea96de")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'circle1)))
  "Returns md5sum for a message object of type 'circle1"
  "ad34fcda4d5e7bd900535ed16cea96de")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<circle1>)))
  "Returns full string definition for message of type '<circle1>"
  (cl:format cl:nil "std_msgs/Header header~%string name~%float32 radius~%float32 center_x~%float32 center_y~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'circle1)))
  "Returns full string definition for message of type 'circle1"
  (cl:format cl:nil "std_msgs/Header header~%string name~%float32 radius~%float32 center_x~%float32 center_y~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <circle1>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:length (cl:slot-value msg 'name))
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <circle1>))
  "Converts a ROS message object to a list"
  (cl:list 'circle1
    (cl:cons ':header (header msg))
    (cl:cons ':name (name msg))
    (cl:cons ':radius (radius msg))
    (cl:cons ':center_x (center_x msg))
    (cl:cons ':center_y (center_y msg))
))
