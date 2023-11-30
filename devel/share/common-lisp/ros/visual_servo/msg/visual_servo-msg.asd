
(cl:in-package :asdf)

(defsystem "visual_servo-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "RobotRelative" :depends-on ("_package_RobotRelative"))
    (:file "_package_RobotRelative" :depends-on ("_package"))
    (:file "circle" :depends-on ("_package_circle"))
    (:file "_package_circle" :depends-on ("_package"))
    (:file "circle1" :depends-on ("_package_circle1"))
    (:file "_package_circle1" :depends-on ("_package"))
    (:file "joint_positon" :depends-on ("_package_joint_positon"))
    (:file "_package_joint_positon" :depends-on ("_package"))
    (:file "pbvs_circles" :depends-on ("_package_pbvs_circles"))
    (:file "_package_pbvs_circles" :depends-on ("_package"))
    (:file "toolposeChange" :depends-on ("_package_toolposeChange"))
    (:file "_package_toolposeChange" :depends-on ("_package"))
  ))