; Auto-generated. Do not edit!


(cl:in-package visual_servo-msg)


;//! \htmlinclude toolposeChange.msg.html

(cl:defclass <toolposeChange> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pose_change
    :reader pose_change
    :initarg :pose_change
    :type (cl:vector cl:float)
   :initform (cl:make-array 16 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass toolposeChange (<toolposeChange>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <toolposeChange>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'toolposeChange)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_servo-msg:<toolposeChange> is deprecated: use visual_servo-msg:toolposeChange instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <toolposeChange>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:header-val is deprecated.  Use visual_servo-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pose_change-val :lambda-list '(m))
(cl:defmethod pose_change-val ((m <toolposeChange>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:pose_change-val is deprecated.  Use visual_servo-msg:pose_change instead.")
  (pose_change m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <toolposeChange>) ostream)
  "Serializes a message object of type '<toolposeChange>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'pose_change))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <toolposeChange>) istream)
  "Deserializes a message object of type '<toolposeChange>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'pose_change) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'pose_change)))
    (cl:dotimes (i 16)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<toolposeChange>)))
  "Returns string type for a message object of type '<toolposeChange>"
  "visual_servo/toolposeChange")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'toolposeChange)))
  "Returns string type for a message object of type 'toolposeChange"
  "visual_servo/toolposeChange")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<toolposeChange>)))
  "Returns md5sum for a message object of type '<toolposeChange>"
  "e5a8098ef919b80fbbf915fe48b2d32d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'toolposeChange)))
  "Returns md5sum for a message object of type 'toolposeChange"
  "e5a8098ef919b80fbbf915fe48b2d32d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<toolposeChange>)))
  "Returns full string definition for message of type '<toolposeChange>"
  (cl:format cl:nil "Header header~%float64[16] pose_change~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'toolposeChange)))
  "Returns full string definition for message of type 'toolposeChange"
  (cl:format cl:nil "Header header~%float64[16] pose_change~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <toolposeChange>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'pose_change) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <toolposeChange>))
  "Converts a ROS message object to a list"
  (cl:list 'toolposeChange
    (cl:cons ':header (header msg))
    (cl:cons ':pose_change (pose_change msg))
))
