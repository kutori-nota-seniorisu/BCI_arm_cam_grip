;; Auto-generated. Do not edit!


(when (boundp 'visual_servo::toolposeChange)
  (if (not (find-package "VISUAL_SERVO"))
    (make-package "VISUAL_SERVO"))
  (shadow 'toolposeChange (find-package "VISUAL_SERVO")))
(unless (find-package "VISUAL_SERVO::TOOLPOSECHANGE")
  (make-package "VISUAL_SERVO::TOOLPOSECHANGE"))

(in-package "ROS")
;;//! \htmlinclude toolposeChange.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass visual_servo::toolposeChange
  :super ros::object
  :slots (_header _pose_change ))

(defmethod visual_servo::toolposeChange
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pose_change __pose_change) (make-array 16 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _pose_change __pose_change)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pose_change
   (&optional __pose_change)
   (if __pose_change (setq _pose_change __pose_change)) _pose_change)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64[16] _pose_change
    (* 8    16)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64[16] _pose_change
     (dotimes (i 16)
       (sys::poke (elt _pose_change i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64[16] _pose_change
   (dotimes (i (length _pose_change))
     (setf (elt _pose_change i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(setf (get visual_servo::toolposeChange :md5sum-) "e5a8098ef919b80fbbf915fe48b2d32d")
(setf (get visual_servo::toolposeChange :datatype-) "visual_servo/toolposeChange")
(setf (get visual_servo::toolposeChange :definition-)
      "Header header
float64[16] pose_change

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



(provide :visual_servo/toolposeChange "e5a8098ef919b80fbbf915fe48b2d32d")


