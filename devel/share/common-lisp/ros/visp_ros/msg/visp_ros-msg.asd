
(cl:in-package :asdf)

(defsystem "visp_ros-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :sensor_msgs-msg
)
  :components ((:file "_package")
    (:file "BlobTracker" :depends-on ("_package_BlobTracker"))
    (:file "_package_BlobTracker" :depends-on ("_package"))
    (:file "ImagePoint" :depends-on ("_package_ImagePoint"))
    (:file "_package_ImagePoint" :depends-on ("_package"))
    (:file "PoseStampedStatus" :depends-on ("_package_PoseStampedStatus"))
    (:file "_package_PoseStampedStatus" :depends-on ("_package"))
    (:file "ProjectedPoint" :depends-on ("_package_ProjectedPoint"))
    (:file "_package_ProjectedPoint" :depends-on ("_package"))
  ))