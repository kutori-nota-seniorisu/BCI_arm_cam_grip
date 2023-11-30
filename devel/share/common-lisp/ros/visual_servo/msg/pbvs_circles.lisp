; Auto-generated. Do not edit!


(cl:in-package visual_servo-msg)


;//! \htmlinclude pbvs_circles.msg.html

(cl:defclass <pbvs_circles> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (circle1
    :reader circle1
    :initarg :circle1
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (circle2
    :reader circle2
    :initarg :circle2
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (circle3
    :reader circle3
    :initarg :circle3
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (circle4
    :reader circle4
    :initarg :circle4
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass pbvs_circles (<pbvs_circles>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pbvs_circles>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pbvs_circles)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visual_servo-msg:<pbvs_circles> is deprecated: use visual_servo-msg:pbvs_circles instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <pbvs_circles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:header-val is deprecated.  Use visual_servo-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'circle1-val :lambda-list '(m))
(cl:defmethod circle1-val ((m <pbvs_circles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:circle1-val is deprecated.  Use visual_servo-msg:circle1 instead.")
  (circle1 m))

(cl:ensure-generic-function 'circle2-val :lambda-list '(m))
(cl:defmethod circle2-val ((m <pbvs_circles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:circle2-val is deprecated.  Use visual_servo-msg:circle2 instead.")
  (circle2 m))

(cl:ensure-generic-function 'circle3-val :lambda-list '(m))
(cl:defmethod circle3-val ((m <pbvs_circles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:circle3-val is deprecated.  Use visual_servo-msg:circle3 instead.")
  (circle3 m))

(cl:ensure-generic-function 'circle4-val :lambda-list '(m))
(cl:defmethod circle4-val ((m <pbvs_circles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visual_servo-msg:circle4-val is deprecated.  Use visual_servo-msg:circle4 instead.")
  (circle4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pbvs_circles>) ostream)
  "Serializes a message object of type '<pbvs_circles>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'circle1))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'circle2))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'circle3))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'circle4))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pbvs_circles>) istream)
  "Deserializes a message object of type '<pbvs_circles>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'circle1) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'circle1)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'circle2) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'circle2)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'circle3) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'circle3)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'circle4) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'circle4)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pbvs_circles>)))
  "Returns string type for a message object of type '<pbvs_circles>"
  "visual_servo/pbvs_circles")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pbvs_circles)))
  "Returns string type for a message object of type 'pbvs_circles"
  "visual_servo/pbvs_circles")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pbvs_circles>)))
  "Returns md5sum for a message object of type '<pbvs_circles>"
  "f98297f55b162ac720ff220dc219f92d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pbvs_circles)))
  "Returns md5sum for a message object of type 'pbvs_circles"
  "f98297f55b162ac720ff220dc219f92d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pbvs_circles>)))
  "Returns full string definition for message of type '<pbvs_circles>"
  (cl:format cl:nil "std_msgs/Header header~%float32[3] circle1~%float32[3] circle2~%float32[3] circle3~%float32[3] circle4~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pbvs_circles)))
  "Returns full string definition for message of type 'pbvs_circles"
  (cl:format cl:nil "std_msgs/Header header~%float32[3] circle1~%float32[3] circle2~%float32[3] circle3~%float32[3] circle4~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pbvs_circles>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'circle1) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'circle2) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'circle3) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'circle4) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pbvs_circles>))
  "Converts a ROS message object to a list"
  (cl:list 'pbvs_circles
    (cl:cons ':header (header msg))
    (cl:cons ':circle1 (circle1 msg))
    (cl:cons ':circle2 (circle2 msg))
    (cl:cons ':circle3 (circle3 msg))
    (cl:cons ':circle4 (circle4 msg))
))
