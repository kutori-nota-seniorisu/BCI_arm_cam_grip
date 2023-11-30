;; Auto-generated. Do not edit!


(when (boundp 'visual_servo::circle1)
  (if (not (find-package "VISUAL_SERVO"))
    (make-package "VISUAL_SERVO"))
  (shadow 'circle1 (find-package "VISUAL_SERVO")))
(unless (find-package "VISUAL_SERVO::CIRCLE1")
  (make-package "VISUAL_SERVO::CIRCLE1"))

(in-package "ROS")
;;//! \htmlinclude circle1.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass visual_servo::circle1
  :super ros::object
  :slots (_header _name _radius _center_x _center_y ))

(defmethod visual_servo::circle1
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:name __name) "")
    ((:radius __radius) 0.0)
    ((:center_x __center_x) 0.0)
    ((:center_y __center_y) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _name (string __name))
   (setq _radius (float __radius))
   (setq _center_x (float __center_x))
   (setq _center_y (float __center_y))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:radius
   (&optional __radius)
   (if __radius (setq _radius __radius)) _radius)
  (:center_x
   (&optional __center_x)
   (if __center_x (setq _center_x __center_x)) _center_x)
  (:center_y
   (&optional __center_y)
   (if __center_y (setq _center_y __center_y)) _center_y)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _name
    4 (length _name)
    ;; float32 _radius
    4
    ;; float32 _center_x
    4
    ;; float32 _center_y
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; float32 _radius
       (sys::poke _radius (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _center_x
       (sys::poke _center_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _center_y
       (sys::poke _center_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32 _radius
     (setq _radius (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _center_x
     (setq _center_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _center_y
     (setq _center_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get visual_servo::circle1 :md5sum-) "ad34fcda4d5e7bd900535ed16cea96de")
(setf (get visual_servo::circle1 :datatype-) "visual_servo/circle1")
(setf (get visual_servo::circle1 :definition-)
      "std_msgs/Header header
string name
float32 radius
float32 center_x
float32 center_y
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



(provide :visual_servo/circle1 "ad34fcda4d5e7bd900535ed16cea96de")


