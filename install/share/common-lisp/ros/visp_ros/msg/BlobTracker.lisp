; Auto-generated. Do not edit!


(cl:in-package visp_ros-msg)


;//! \htmlinclude BlobTracker.msg.html

(cl:defclass <BlobTracker> (roslisp-msg-protocol:ros-message)
  ((pose_stamped
    :reader pose_stamped
    :initarg :pose_stamped
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped))
   (image
    :reader image
    :initarg :image
    :type sensor_msgs-msg:Image
    :initform (cl:make-instance 'sensor_msgs-msg:Image))
   (blob_cogs
    :reader blob_cogs
    :initarg :blob_cogs
    :type (cl:vector visp_ros-msg:ImagePoint)
   :initform (cl:make-array 0 :element-type 'visp_ros-msg:ImagePoint :initial-element (cl:make-instance 'visp_ros-msg:ImagePoint)))
   (blob_proj
    :reader blob_proj
    :initarg :blob_proj
    :type (cl:vector visp_ros-msg:ProjectedPoint)
   :initform (cl:make-array 0 :element-type 'visp_ros-msg:ProjectedPoint :initial-element (cl:make-instance 'visp_ros-msg:ProjectedPoint))))
)

(cl:defclass BlobTracker (<BlobTracker>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BlobTracker>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BlobTracker)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name visp_ros-msg:<BlobTracker> is deprecated: use visp_ros-msg:BlobTracker instead.")))

(cl:ensure-generic-function 'pose_stamped-val :lambda-list '(m))
(cl:defmethod pose_stamped-val ((m <BlobTracker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visp_ros-msg:pose_stamped-val is deprecated.  Use visp_ros-msg:pose_stamped instead.")
  (pose_stamped m))

(cl:ensure-generic-function 'image-val :lambda-list '(m))
(cl:defmethod image-val ((m <BlobTracker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visp_ros-msg:image-val is deprecated.  Use visp_ros-msg:image instead.")
  (image m))

(cl:ensure-generic-function 'blob_cogs-val :lambda-list '(m))
(cl:defmethod blob_cogs-val ((m <BlobTracker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visp_ros-msg:blob_cogs-val is deprecated.  Use visp_ros-msg:blob_cogs instead.")
  (blob_cogs m))

(cl:ensure-generic-function 'blob_proj-val :lambda-list '(m))
(cl:defmethod blob_proj-val ((m <BlobTracker>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader visp_ros-msg:blob_proj-val is deprecated.  Use visp_ros-msg:blob_proj instead.")
  (blob_proj m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BlobTracker>) ostream)
  "Serializes a message object of type '<BlobTracker>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose_stamped) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'image) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'blob_cogs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'blob_cogs))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'blob_proj))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'blob_proj))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BlobTracker>) istream)
  "Deserializes a message object of type '<BlobTracker>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose_stamped) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'image) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'blob_cogs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'blob_cogs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'visp_ros-msg:ImagePoint))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'blob_proj) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'blob_proj)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'visp_ros-msg:ProjectedPoint))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BlobTracker>)))
  "Returns string type for a message object of type '<BlobTracker>"
  "visp_ros/BlobTracker")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BlobTracker)))
  "Returns string type for a message object of type 'BlobTracker"
  "visp_ros/BlobTracker")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BlobTracker>)))
  "Returns md5sum for a message object of type '<BlobTracker>"
  "0dc82e760baf9b1ef9beb061604f3e2a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BlobTracker)))
  "Returns md5sum for a message object of type 'BlobTracker"
  "0dc82e760baf9b1ef9beb061604f3e2a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BlobTracker>)))
  "Returns full string definition for message of type '<BlobTracker>"
  (cl:format cl:nil "geometry_msgs/PoseStamped pose_stamped~%sensor_msgs/Image image~%ImagePoint[] blob_cogs~%ProjectedPoint[] blob_proj~%~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: sensor_msgs/Image~%# This message contains an uncompressed image~%# (0, 0) is at top-left corner of image~%#~%~%Header header        # Header timestamp should be acquisition time of image~%                     # Header frame_id should be optical frame of camera~%                     # origin of frame should be optical center of camera~%                     # +x should point to the right in the image~%                     # +y should point down in the image~%                     # +z should point into to plane of the image~%                     # If the frame_id here and the frame_id of the CameraInfo~%                     # message associated with the image conflict~%                     # the behavior is undefined~%~%uint32 height         # image height, that is, number of rows~%uint32 width          # image width, that is, number of columns~%~%# The legal values for encoding are in file src/image_encodings.cpp~%# If you want to standardize a new string format, join~%# ros-users@lists.sourceforge.net and send an email proposing a new encoding.~%~%string encoding       # Encoding of pixels -- channel meaning, ordering, size~%                      # taken from the list of strings in include/sensor_msgs/image_encodings.h~%~%uint8 is_bigendian    # is this data bigendian?~%uint32 step           # Full row length in bytes~%uint8[] data          # actual matrix data, size is (step * rows)~%~%================================================================================~%MSG: visp_ros/ImagePoint~%# Message corresponding to vpImagePoint class~%float64 i      # i (respectively v) position in the image~%float64 j      # j (respectively u) position in the image~%~%~%================================================================================~%MSG: visp_ros/ProjectedPoint~%# Message corresponding to coordinates of the point after perspective projection~%float64 x      # Coordinate of the point in the image plane in meter along X axis~%float64 y      # Coordinate of the point in the image plane in meter along Y axis~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BlobTracker)))
  "Returns full string definition for message of type 'BlobTracker"
  (cl:format cl:nil "geometry_msgs/PoseStamped pose_stamped~%sensor_msgs/Image image~%ImagePoint[] blob_cogs~%ProjectedPoint[] blob_proj~%~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: sensor_msgs/Image~%# This message contains an uncompressed image~%# (0, 0) is at top-left corner of image~%#~%~%Header header        # Header timestamp should be acquisition time of image~%                     # Header frame_id should be optical frame of camera~%                     # origin of frame should be optical center of camera~%                     # +x should point to the right in the image~%                     # +y should point down in the image~%                     # +z should point into to plane of the image~%                     # If the frame_id here and the frame_id of the CameraInfo~%                     # message associated with the image conflict~%                     # the behavior is undefined~%~%uint32 height         # image height, that is, number of rows~%uint32 width          # image width, that is, number of columns~%~%# The legal values for encoding are in file src/image_encodings.cpp~%# If you want to standardize a new string format, join~%# ros-users@lists.sourceforge.net and send an email proposing a new encoding.~%~%string encoding       # Encoding of pixels -- channel meaning, ordering, size~%                      # taken from the list of strings in include/sensor_msgs/image_encodings.h~%~%uint8 is_bigendian    # is this data bigendian?~%uint32 step           # Full row length in bytes~%uint8[] data          # actual matrix data, size is (step * rows)~%~%================================================================================~%MSG: visp_ros/ImagePoint~%# Message corresponding to vpImagePoint class~%float64 i      # i (respectively v) position in the image~%float64 j      # j (respectively u) position in the image~%~%~%================================================================================~%MSG: visp_ros/ProjectedPoint~%# Message corresponding to coordinates of the point after perspective projection~%float64 x      # Coordinate of the point in the image plane in meter along X axis~%float64 y      # Coordinate of the point in the image plane in meter along Y axis~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BlobTracker>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose_stamped))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'image))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'blob_cogs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'blob_proj) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BlobTracker>))
  "Converts a ROS message object to a list"
  (cl:list 'BlobTracker
    (cl:cons ':pose_stamped (pose_stamped msg))
    (cl:cons ':image (image msg))
    (cl:cons ':blob_cogs (blob_cogs msg))
    (cl:cons ':blob_proj (blob_proj msg))
))
