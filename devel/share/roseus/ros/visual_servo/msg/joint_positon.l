;; Auto-generated. Do not edit!


(when (boundp 'visual_servo::joint_positon)
  (if (not (find-package "VISUAL_SERVO"))
    (make-package "VISUAL_SERVO"))
  (shadow 'joint_positon (find-package "VISUAL_SERVO")))
(unless (find-package "VISUAL_SERVO::JOINT_POSITON")
  (make-package "VISUAL_SERVO::JOINT_POSITON"))

(in-package "ROS")
;;//! \htmlinclude joint_positon.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass visual_servo::joint_positon
  :super ros::object
  :slots (_header _shoulder_pan_joint _shoulder_lift_joint _elbow_joint _wrist_1_joint _wrist_2_joint _wrist_3_joint ))

(defmethod visual_servo::joint_positon
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:shoulder_pan_joint __shoulder_pan_joint) 0.0)
    ((:shoulder_lift_joint __shoulder_lift_joint) 0.0)
    ((:elbow_joint __elbow_joint) 0.0)
    ((:wrist_1_joint __wrist_1_joint) 0.0)
    ((:wrist_2_joint __wrist_2_joint) 0.0)
    ((:wrist_3_joint __wrist_3_joint) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _shoulder_pan_joint (float __shoulder_pan_joint))
   (setq _shoulder_lift_joint (float __shoulder_lift_joint))
   (setq _elbow_joint (float __elbow_joint))
   (setq _wrist_1_joint (float __wrist_1_joint))
   (setq _wrist_2_joint (float __wrist_2_joint))
   (setq _wrist_3_joint (float __wrist_3_joint))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:shoulder_pan_joint
   (&optional __shoulder_pan_joint)
   (if __shoulder_pan_joint (setq _shoulder_pan_joint __shoulder_pan_joint)) _shoulder_pan_joint)
  (:shoulder_lift_joint
   (&optional __shoulder_lift_joint)
   (if __shoulder_lift_joint (setq _shoulder_lift_joint __shoulder_lift_joint)) _shoulder_lift_joint)
  (:elbow_joint
   (&optional __elbow_joint)
   (if __elbow_joint (setq _elbow_joint __elbow_joint)) _elbow_joint)
  (:wrist_1_joint
   (&optional __wrist_1_joint)
   (if __wrist_1_joint (setq _wrist_1_joint __wrist_1_joint)) _wrist_1_joint)
  (:wrist_2_joint
   (&optional __wrist_2_joint)
   (if __wrist_2_joint (setq _wrist_2_joint __wrist_2_joint)) _wrist_2_joint)
  (:wrist_3_joint
   (&optional __wrist_3_joint)
   (if __wrist_3_joint (setq _wrist_3_joint __wrist_3_joint)) _wrist_3_joint)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _shoulder_pan_joint
    4
    ;; float32 _shoulder_lift_joint
    4
    ;; float32 _elbow_joint
    4
    ;; float32 _wrist_1_joint
    4
    ;; float32 _wrist_2_joint
    4
    ;; float32 _wrist_3_joint
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _shoulder_pan_joint
       (sys::poke _shoulder_pan_joint (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _shoulder_lift_joint
       (sys::poke _shoulder_lift_joint (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _elbow_joint
       (sys::poke _elbow_joint (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wrist_1_joint
       (sys::poke _wrist_1_joint (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wrist_2_joint
       (sys::poke _wrist_2_joint (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wrist_3_joint
       (sys::poke _wrist_3_joint (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _shoulder_pan_joint
     (setq _shoulder_pan_joint (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _shoulder_lift_joint
     (setq _shoulder_lift_joint (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _elbow_joint
     (setq _elbow_joint (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wrist_1_joint
     (setq _wrist_1_joint (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wrist_2_joint
     (setq _wrist_2_joint (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wrist_3_joint
     (setq _wrist_3_joint (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get visual_servo::joint_positon :md5sum-) "a82fc01b03f66381c43297a78b5259f1")
(setf (get visual_servo::joint_positon :datatype-) "visual_servo/joint_positon")
(setf (get visual_servo::joint_positon :definition-)
      "std_msgs/Header header
float32 shoulder_pan_joint
float32 shoulder_lift_joint
float32 elbow_joint
float32 wrist_1_joint
float32 wrist_2_joint
float32 wrist_3_joint

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



(provide :visual_servo/joint_positon "a82fc01b03f66381c43297a78b5259f1")


