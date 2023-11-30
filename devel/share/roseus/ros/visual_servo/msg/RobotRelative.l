;; Auto-generated. Do not edit!


(when (boundp 'visual_servo::RobotRelative)
  (if (not (find-package "VISUAL_SERVO"))
    (make-package "VISUAL_SERVO"))
  (shadow 'RobotRelative (find-package "VISUAL_SERVO")))
(unless (find-package "VISUAL_SERVO::ROBOTRELATIVE")
  (make-package "VISUAL_SERVO::ROBOTRELATIVE"))

(in-package "ROS")
;;//! \htmlinclude RobotRelative.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass visual_servo::RobotRelative
  :super ros::object
  :slots (_header _actualTCPPose _targetTCPPose _actualTCPSpeed _targetTCPSpeed _actualTCPForce _actualToolAccel _actualJointPosition _end2base _digitalInputBits ))

(defmethod visual_servo::RobotRelative
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:actualTCPPose __actualTCPPose) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:targetTCPPose __targetTCPPose) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:actualTCPSpeed __actualTCPSpeed) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:targetTCPSpeed __targetTCPSpeed) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:actualTCPForce __actualTCPForce) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:actualToolAccel __actualToolAccel) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:actualJointPosition __actualJointPosition) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:end2base __end2base) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:digitalInputBits __digitalInputBits) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _actualTCPPose __actualTCPPose)
   (setq _targetTCPPose __targetTCPPose)
   (setq _actualTCPSpeed __actualTCPSpeed)
   (setq _targetTCPSpeed __targetTCPSpeed)
   (setq _actualTCPForce __actualTCPForce)
   (setq _actualToolAccel __actualToolAccel)
   (setq _actualJointPosition __actualJointPosition)
   (setq _end2base __end2base)
   (setq _digitalInputBits (round __digitalInputBits))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:actualTCPPose
   (&optional __actualTCPPose)
   (if __actualTCPPose (setq _actualTCPPose __actualTCPPose)) _actualTCPPose)
  (:targetTCPPose
   (&optional __targetTCPPose)
   (if __targetTCPPose (setq _targetTCPPose __targetTCPPose)) _targetTCPPose)
  (:actualTCPSpeed
   (&optional __actualTCPSpeed)
   (if __actualTCPSpeed (setq _actualTCPSpeed __actualTCPSpeed)) _actualTCPSpeed)
  (:targetTCPSpeed
   (&optional __targetTCPSpeed)
   (if __targetTCPSpeed (setq _targetTCPSpeed __targetTCPSpeed)) _targetTCPSpeed)
  (:actualTCPForce
   (&optional __actualTCPForce)
   (if __actualTCPForce (setq _actualTCPForce __actualTCPForce)) _actualTCPForce)
  (:actualToolAccel
   (&optional __actualToolAccel)
   (if __actualToolAccel (setq _actualToolAccel __actualToolAccel)) _actualToolAccel)
  (:actualJointPosition
   (&optional __actualJointPosition)
   (if __actualJointPosition (setq _actualJointPosition __actualJointPosition)) _actualJointPosition)
  (:end2base
   (&optional __end2base)
   (if __end2base (setq _end2base __end2base)) _end2base)
  (:digitalInputBits
   (&optional __digitalInputBits)
   (if __digitalInputBits (setq _digitalInputBits __digitalInputBits)) _digitalInputBits)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64[] _actualTCPPose
    (* 8    (length _actualTCPPose)) 4
    ;; float64[] _targetTCPPose
    (* 8    (length _targetTCPPose)) 4
    ;; float64[] _actualTCPSpeed
    (* 8    (length _actualTCPSpeed)) 4
    ;; float64[] _targetTCPSpeed
    (* 8    (length _targetTCPSpeed)) 4
    ;; float64[] _actualTCPForce
    (* 8    (length _actualTCPForce)) 4
    ;; float64[] _actualToolAccel
    (* 8    (length _actualToolAccel)) 4
    ;; float64[] _actualJointPosition
    (* 8    (length _actualJointPosition)) 4
    ;; float64[] _end2base
    (* 8    (length _end2base)) 4
    ;; int64 _digitalInputBits
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64[] _actualTCPPose
     (write-long (length _actualTCPPose) s)
     (dotimes (i (length _actualTCPPose))
       (sys::poke (elt _actualTCPPose i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _targetTCPPose
     (write-long (length _targetTCPPose) s)
     (dotimes (i (length _targetTCPPose))
       (sys::poke (elt _targetTCPPose i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _actualTCPSpeed
     (write-long (length _actualTCPSpeed) s)
     (dotimes (i (length _actualTCPSpeed))
       (sys::poke (elt _actualTCPSpeed i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _targetTCPSpeed
     (write-long (length _targetTCPSpeed) s)
     (dotimes (i (length _targetTCPSpeed))
       (sys::poke (elt _targetTCPSpeed i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _actualTCPForce
     (write-long (length _actualTCPForce) s)
     (dotimes (i (length _actualTCPForce))
       (sys::poke (elt _actualTCPForce i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _actualToolAccel
     (write-long (length _actualToolAccel) s)
     (dotimes (i (length _actualToolAccel))
       (sys::poke (elt _actualToolAccel i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _actualJointPosition
     (write-long (length _actualJointPosition) s)
     (dotimes (i (length _actualJointPosition))
       (sys::poke (elt _actualJointPosition i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _end2base
     (write-long (length _end2base) s)
     (dotimes (i (length _end2base))
       (sys::poke (elt _end2base i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; int64 _digitalInputBits
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _digitalInputBits (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _digitalInputBits) (= (length (_digitalInputBits . bv)) 2)) ;; bignum
              (write-long (ash (elt (_digitalInputBits . bv) 0) 0) s)
              (write-long (ash (elt (_digitalInputBits . bv) 1) -1) s))
             ((and (class _digitalInputBits) (= (length (_digitalInputBits . bv)) 1)) ;; big1
              (write-long (elt (_digitalInputBits . bv) 0) s)
              (write-long (if (>= _digitalInputBits 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _digitalInputBits s)(write-long (if (>= _digitalInputBits 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64[] _actualTCPPose
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _actualTCPPose (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _actualTCPPose i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _targetTCPPose
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _targetTCPPose (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _targetTCPPose i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _actualTCPSpeed
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _actualTCPSpeed (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _actualTCPSpeed i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _targetTCPSpeed
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _targetTCPSpeed (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _targetTCPSpeed i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _actualTCPForce
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _actualTCPForce (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _actualTCPForce i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _actualToolAccel
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _actualToolAccel (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _actualToolAccel i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _actualJointPosition
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _actualJointPosition (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _actualJointPosition i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _end2base
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _end2base (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _end2base i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; int64 _digitalInputBits
#+(or :alpha :irix6 :x86_64)
      (setf _digitalInputBits (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _digitalInputBits (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(setf (get visual_servo::RobotRelative :md5sum-) "43b4d3212a47865eb33311ebedb438ce")
(setf (get visual_servo::RobotRelative :datatype-) "visual_servo/RobotRelative")
(setf (get visual_servo::RobotRelative :definition-)
      "Header header
float64[] actualTCPPose
float64[] targetTCPPose
float64[] actualTCPSpeed
float64[] targetTCPSpeed
float64[] actualTCPForce
float64[] actualToolAccel
float64[] actualJointPosition
float64[] end2base
int64 digitalInputBits



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



(provide :visual_servo/RobotRelative "43b4d3212a47865eb33311ebedb438ce")


