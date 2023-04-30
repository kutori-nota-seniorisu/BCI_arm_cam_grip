;; Auto-generated. Do not edit!


(when (boundp 'visp_ros::BlobTracker)
  (if (not (find-package "VISP_ROS"))
    (make-package "VISP_ROS"))
  (shadow 'BlobTracker (find-package "VISP_ROS")))
(unless (find-package "VISP_ROS::BLOBTRACKER")
  (make-package "VISP_ROS::BLOBTRACKER"))

(in-package "ROS")
;;//! \htmlinclude BlobTracker.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass visp_ros::BlobTracker
  :super ros::object
  :slots (_pose_stamped _image _blob_cogs _blob_proj ))

(defmethod visp_ros::BlobTracker
  (:init
   (&key
    ((:pose_stamped __pose_stamped) (instance geometry_msgs::PoseStamped :init))
    ((:image __image) (instance sensor_msgs::Image :init))
    ((:blob_cogs __blob_cogs) (let (r) (dotimes (i 0) (push (instance visp_ros::ImagePoint :init) r)) r))
    ((:blob_proj __blob_proj) (let (r) (dotimes (i 0) (push (instance visp_ros::ProjectedPoint :init) r)) r))
    )
   (send-super :init)
   (setq _pose_stamped __pose_stamped)
   (setq _image __image)
   (setq _blob_cogs __blob_cogs)
   (setq _blob_proj __blob_proj)
   self)
  (:pose_stamped
   (&rest __pose_stamped)
   (if (keywordp (car __pose_stamped))
       (send* _pose_stamped __pose_stamped)
     (progn
       (if __pose_stamped (setq _pose_stamped (car __pose_stamped)))
       _pose_stamped)))
  (:image
   (&rest __image)
   (if (keywordp (car __image))
       (send* _image __image)
     (progn
       (if __image (setq _image (car __image)))
       _image)))
  (:blob_cogs
   (&rest __blob_cogs)
   (if (keywordp (car __blob_cogs))
       (send* _blob_cogs __blob_cogs)
     (progn
       (if __blob_cogs (setq _blob_cogs (car __blob_cogs)))
       _blob_cogs)))
  (:blob_proj
   (&rest __blob_proj)
   (if (keywordp (car __blob_proj))
       (send* _blob_proj __blob_proj)
     (progn
       (if __blob_proj (setq _blob_proj (car __blob_proj)))
       _blob_proj)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/PoseStamped _pose_stamped
    (send _pose_stamped :serialization-length)
    ;; sensor_msgs/Image _image
    (send _image :serialization-length)
    ;; visp_ros/ImagePoint[] _blob_cogs
    (apply #'+ (send-all _blob_cogs :serialization-length)) 4
    ;; visp_ros/ProjectedPoint[] _blob_proj
    (apply #'+ (send-all _blob_proj :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/PoseStamped _pose_stamped
       (send _pose_stamped :serialize s)
     ;; sensor_msgs/Image _image
       (send _image :serialize s)
     ;; visp_ros/ImagePoint[] _blob_cogs
     (write-long (length _blob_cogs) s)
     (dolist (elem _blob_cogs)
       (send elem :serialize s)
       )
     ;; visp_ros/ProjectedPoint[] _blob_proj
     (write-long (length _blob_proj) s)
     (dolist (elem _blob_proj)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/PoseStamped _pose_stamped
     (send _pose_stamped :deserialize buf ptr-) (incf ptr- (send _pose_stamped :serialization-length))
   ;; sensor_msgs/Image _image
     (send _image :deserialize buf ptr-) (incf ptr- (send _image :serialization-length))
   ;; visp_ros/ImagePoint[] _blob_cogs
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _blob_cogs (let (r) (dotimes (i n) (push (instance visp_ros::ImagePoint :init) r)) r))
     (dolist (elem- _blob_cogs)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; visp_ros/ProjectedPoint[] _blob_proj
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _blob_proj (let (r) (dotimes (i n) (push (instance visp_ros::ProjectedPoint :init) r)) r))
     (dolist (elem- _blob_proj)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get visp_ros::BlobTracker :md5sum-) "0dc82e760baf9b1ef9beb061604f3e2a")
(setf (get visp_ros::BlobTracker :datatype-) "visp_ros/BlobTracker")
(setf (get visp_ros::BlobTracker :definition-)
      "geometry_msgs/PoseStamped pose_stamped
sensor_msgs/Image image
ImagePoint[] blob_cogs
ProjectedPoint[] blob_proj


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

================================================================================
MSG: sensor_msgs/Image
# This message contains an uncompressed image
# (0, 0) is at top-left corner of image
#

Header header        # Header timestamp should be acquisition time of image
                     # Header frame_id should be optical frame of camera
                     # origin of frame should be optical center of camera
                     # +x should point to the right in the image
                     # +y should point down in the image
                     # +z should point into to plane of the image
                     # If the frame_id here and the frame_id of the CameraInfo
                     # message associated with the image conflict
                     # the behavior is undefined

uint32 height         # image height, that is, number of rows
uint32 width          # image width, that is, number of columns

# The legal values for encoding are in file src/image_encodings.cpp
# If you want to standardize a new string format, join
# ros-users@lists.sourceforge.net and send an email proposing a new encoding.

string encoding       # Encoding of pixels -- channel meaning, ordering, size
                      # taken from the list of strings in include/sensor_msgs/image_encodings.h

uint8 is_bigendian    # is this data bigendian?
uint32 step           # Full row length in bytes
uint8[] data          # actual matrix data, size is (step * rows)

================================================================================
MSG: visp_ros/ImagePoint
# Message corresponding to vpImagePoint class
float64 i      # i (respectively v) position in the image
float64 j      # j (respectively u) position in the image


================================================================================
MSG: visp_ros/ProjectedPoint
# Message corresponding to coordinates of the point after perspective projection
float64 x      # Coordinate of the point in the image plane in meter along X axis
float64 y      # Coordinate of the point in the image plane in meter along Y axis


")



(provide :visp_ros/BlobTracker "0dc82e760baf9b1ef9beb061604f3e2a")


