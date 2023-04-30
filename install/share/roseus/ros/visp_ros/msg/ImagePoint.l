;; Auto-generated. Do not edit!


(when (boundp 'visp_ros::ImagePoint)
  (if (not (find-package "VISP_ROS"))
    (make-package "VISP_ROS"))
  (shadow 'ImagePoint (find-package "VISP_ROS")))
(unless (find-package "VISP_ROS::IMAGEPOINT")
  (make-package "VISP_ROS::IMAGEPOINT"))

(in-package "ROS")
;;//! \htmlinclude ImagePoint.msg.html


(defclass visp_ros::ImagePoint
  :super ros::object
  :slots (_i _j ))

(defmethod visp_ros::ImagePoint
  (:init
   (&key
    ((:i __i) 0.0)
    ((:j __j) 0.0)
    )
   (send-super :init)
   (setq _i (float __i))
   (setq _j (float __j))
   self)
  (:i
   (&optional __i)
   (if __i (setq _i __i)) _i)
  (:j
   (&optional __j)
   (if __j (setq _j __j)) _j)
  (:serialization-length
   ()
   (+
    ;; float64 _i
    8
    ;; float64 _j
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _i
       (sys::poke _i (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _j
       (sys::poke _j (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _i
     (setq _i (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _j
     (setq _j (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get visp_ros::ImagePoint :md5sum-) "600c777d3f6d5d378f3fc5f8df469dbe")
(setf (get visp_ros::ImagePoint :datatype-) "visp_ros/ImagePoint")
(setf (get visp_ros::ImagePoint :definition-)
      "# Message corresponding to vpImagePoint class
float64 i      # i (respectively v) position in the image
float64 j      # j (respectively u) position in the image


")



(provide :visp_ros/ImagePoint "600c777d3f6d5d378f3fc5f8df469dbe")


