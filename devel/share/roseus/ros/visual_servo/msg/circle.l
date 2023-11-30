;; Auto-generated. Do not edit!


(when (boundp 'visual_servo::circle)
  (if (not (find-package "VISUAL_SERVO"))
    (make-package "VISUAL_SERVO"))
  (shadow 'circle (find-package "VISUAL_SERVO")))
(unless (find-package "VISUAL_SERVO::CIRCLE")
  (make-package "VISUAL_SERVO::CIRCLE"))

(in-package "ROS")
;;//! \htmlinclude circle.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass visual_servo::circle
  :super ros::object
  :slots (_header _u _v _depth ))

(defmethod visual_servo::circle
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:u __u) 0.0)
    ((:v __v) 0.0)
    ((:depth __depth) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _u (float __u))
   (setq _v (float __v))
   (setq _depth (float __depth))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:u
   (&optional __u)
   (if __u (setq _u __u)) _u)
  (:v
   (&optional __v)
   (if __v (setq _v __v)) _v)
  (:depth
   (&optional __depth)
   (if __depth (setq _depth __depth)) _depth)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _u
    4
    ;; float32 _v
    4
    ;; float32 _depth
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _u
       (sys::poke _u (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _v
       (sys::poke _v (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _depth
       (sys::poke _depth (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _u
     (setq _u (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _v
     (setq _v (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _depth
     (setq _depth (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get visual_servo::circle :md5sum-) "19441ccc19436b3bb7eded013d980ace")
(setf (get visual_servo::circle :datatype-) "visual_servo/circle")
(setf (get visual_servo::circle :definition-)
      "std_msgs/Header header
float32 u
float32 v
float32 depth

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

")



(provide :visual_servo/circle "19441ccc19436b3bb7eded013d980ace")


