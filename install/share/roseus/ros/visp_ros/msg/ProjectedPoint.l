;; Auto-generated. Do not edit!


(when (boundp 'visp_ros::ProjectedPoint)
  (if (not (find-package "VISP_ROS"))
    (make-package "VISP_ROS"))
  (shadow 'ProjectedPoint (find-package "VISP_ROS")))
(unless (find-package "VISP_ROS::PROJECTEDPOINT")
  (make-package "VISP_ROS::PROJECTEDPOINT"))

(in-package "ROS")
;;//! \htmlinclude ProjectedPoint.msg.html


(defclass visp_ros::ProjectedPoint
  :super ros::object
  :slots (_x _y ))

(defmethod visp_ros::ProjectedPoint
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get visp_ros::ProjectedPoint :md5sum-) "209f516d3eb691f0663e25cb750d67c1")
(setf (get visp_ros::ProjectedPoint :datatype-) "visp_ros/ProjectedPoint")
(setf (get visp_ros::ProjectedPoint :definition-)
      "# Message corresponding to coordinates of the point after perspective projection
float64 x      # Coordinate of the point in the image plane in meter along X axis
float64 y      # Coordinate of the point in the image plane in meter along Y axis


")



(provide :visp_ros/ProjectedPoint "209f516d3eb691f0663e25cb750d67c1")


