;; Auto-generated. Do not edit!


(when (boundp 'visual_servo::pbvs_circles)
  (if (not (find-package "VISUAL_SERVO"))
    (make-package "VISUAL_SERVO"))
  (shadow 'pbvs_circles (find-package "VISUAL_SERVO")))
(unless (find-package "VISUAL_SERVO::PBVS_CIRCLES")
  (make-package "VISUAL_SERVO::PBVS_CIRCLES"))

(in-package "ROS")
;;//! \htmlinclude pbvs_circles.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass visual_servo::pbvs_circles
  :super ros::object
  :slots (_header _circle1 _circle2 _circle3 _circle4 ))

(defmethod visual_servo::pbvs_circles
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:circle1 __circle1) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:circle2 __circle2) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:circle3 __circle3) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:circle4 __circle4) (make-array 3 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _circle1 __circle1)
   (setq _circle2 __circle2)
   (setq _circle3 __circle3)
   (setq _circle4 __circle4)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:circle1
   (&optional __circle1)
   (if __circle1 (setq _circle1 __circle1)) _circle1)
  (:circle2
   (&optional __circle2)
   (if __circle2 (setq _circle2 __circle2)) _circle2)
  (:circle3
   (&optional __circle3)
   (if __circle3 (setq _circle3 __circle3)) _circle3)
  (:circle4
   (&optional __circle4)
   (if __circle4 (setq _circle4 __circle4)) _circle4)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32[3] _circle1
    (* 4    3)
    ;; float32[3] _circle2
    (* 4    3)
    ;; float32[3] _circle3
    (* 4    3)
    ;; float32[3] _circle4
    (* 4    3)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32[3] _circle1
     (dotimes (i 3)
       (sys::poke (elt _circle1 i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _circle2
     (dotimes (i 3)
       (sys::poke (elt _circle2 i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _circle3
     (dotimes (i 3)
       (sys::poke (elt _circle3 i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _circle4
     (dotimes (i 3)
       (sys::poke (elt _circle4 i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32[3] _circle1
   (dotimes (i (length _circle1))
     (setf (elt _circle1 i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _circle2
   (dotimes (i (length _circle2))
     (setf (elt _circle2 i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _circle3
   (dotimes (i (length _circle3))
     (setf (elt _circle3 i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _circle4
   (dotimes (i (length _circle4))
     (setf (elt _circle4 i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get visual_servo::pbvs_circles :md5sum-) "f98297f55b162ac720ff220dc219f92d")
(setf (get visual_servo::pbvs_circles :datatype-) "visual_servo/pbvs_circles")
(setf (get visual_servo::pbvs_circles :definition-)
      "std_msgs/Header header
float32[3] circle1
float32[3] circle2
float32[3] circle3
float32[3] circle4

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



(provide :visual_servo/pbvs_circles "f98297f55b162ac720ff220dc219f92d")


