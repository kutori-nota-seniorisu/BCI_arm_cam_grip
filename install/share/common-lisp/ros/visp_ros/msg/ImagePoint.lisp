; Auto-generated. Do not edit!


(cl:in-package visp_ros-msg)


;//! \htmlinclude ImagePoint.msg.html

(cl:defclass <ImagePoint> (roslisp-msg-protocol:ros-message)
  ((i
    :reader i
    :initarg :i
    :type cl:float
    :initform 0.0)
   (j
    :reader j
    :initarg :j
    :type cl:float
    :initform 0.0))
)

(cl:defclass ImagePoint (<ImagePoint>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ImagePoint>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ImagePoint)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visp_ros-msg:<ImagePoint> is deprecated: use visp_ros-msg:ImagePoint instead.")))

(cl:ensure-generic-function 'i-val :lambda-list '(m))
(cl:defmethod i-val ((m <ImagePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visp_ros-msg:i-val is deprecated.  Use visp_ros-msg:i instead.")
  (i m))

(cl:ensure-generic-function 'j-val :lambda-list '(m))
(cl:defmethod j-val ((m <ImagePoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visp_ros-msg:j-val is deprecated.  Use visp_ros-msg:j instead.")
  (j m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ImagePoint>) ostream)
  "Serializes a message object of type '<ImagePoint>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'i))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'j))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ImagePoint>) istream)
  "Deserializes a message object of type '<ImagePoint>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'i) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'j) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ImagePoint>)))
  "Returns string type for a message object of type '<ImagePoint>"
  "visp_ros/ImagePoint")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ImagePoint)))
  "Returns string type for a message object of type 'ImagePoint"
  "visp_ros/ImagePoint")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ImagePoint>)))
  "Returns md5sum for a message object of type '<ImagePoint>"
  "600c777d3f6d5d378f3fc5f8df469dbe")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ImagePoint)))
  "Returns md5sum for a message object of type 'ImagePoint"
  "600c777d3f6d5d378f3fc5f8df469dbe")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ImagePoint>)))
  "Returns full string definition for message of type '<ImagePoint>"
  (cl:format cl:nil "# Message corresponding to vpImagePoint class~%float64 i      # i (respectively v) position in the image~%float64 j      # j (respectively u) position in the image~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ImagePoint)))
  "Returns full string definition for message of type 'ImagePoint"
  (cl:format cl:nil "# Message corresponding to vpImagePoint class~%float64 i      # i (respectively v) position in the image~%float64 j      # j (respectively u) position in the image~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ImagePoint>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ImagePoint>))
  "Converts a ROS message object to a list"
  (cl:list 'ImagePoint
    (cl:cons ':i (i msg))
    (cl:cons ':j (j msg))
))
