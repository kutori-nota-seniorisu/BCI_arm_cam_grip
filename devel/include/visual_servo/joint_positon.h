// Generated by gencpp from file visual_servo/joint_positon.msg
// DO NOT EDIT!


#ifndef VISUAL_SERVO_MESSAGE_JOINT_POSITON_H
#define VISUAL_SERVO_MESSAGE_JOINT_POSITON_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace visual_servo
{
template <class ContainerAllocator>
struct joint_positon_
{
  typedef joint_positon_<ContainerAllocator> Type;

  joint_positon_()
    : header()
    , shoulder_pan_joint(0.0)
    , shoulder_lift_joint(0.0)
    , elbow_joint(0.0)
    , wrist_1_joint(0.0)
    , wrist_2_joint(0.0)
    , wrist_3_joint(0.0)  {
    }
  joint_positon_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , shoulder_pan_joint(0.0)
    , shoulder_lift_joint(0.0)
    , elbow_joint(0.0)
    , wrist_1_joint(0.0)
    , wrist_2_joint(0.0)
    , wrist_3_joint(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef float _shoulder_pan_joint_type;
  _shoulder_pan_joint_type shoulder_pan_joint;

   typedef float _shoulder_lift_joint_type;
  _shoulder_lift_joint_type shoulder_lift_joint;

   typedef float _elbow_joint_type;
  _elbow_joint_type elbow_joint;

   typedef float _wrist_1_joint_type;
  _wrist_1_joint_type wrist_1_joint;

   typedef float _wrist_2_joint_type;
  _wrist_2_joint_type wrist_2_joint;

   typedef float _wrist_3_joint_type;
  _wrist_3_joint_type wrist_3_joint;





  typedef boost::shared_ptr< ::visual_servo::joint_positon_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::visual_servo::joint_positon_<ContainerAllocator> const> ConstPtr;

}; // struct joint_positon_

typedef ::visual_servo::joint_positon_<std::allocator<void> > joint_positon;

typedef boost::shared_ptr< ::visual_servo::joint_positon > joint_positonPtr;
typedef boost::shared_ptr< ::visual_servo::joint_positon const> joint_positonConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::visual_servo::joint_positon_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::visual_servo::joint_positon_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::visual_servo::joint_positon_<ContainerAllocator1> & lhs, const ::visual_servo::joint_positon_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.shoulder_pan_joint == rhs.shoulder_pan_joint &&
    lhs.shoulder_lift_joint == rhs.shoulder_lift_joint &&
    lhs.elbow_joint == rhs.elbow_joint &&
    lhs.wrist_1_joint == rhs.wrist_1_joint &&
    lhs.wrist_2_joint == rhs.wrist_2_joint &&
    lhs.wrist_3_joint == rhs.wrist_3_joint;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::visual_servo::joint_positon_<ContainerAllocator1> & lhs, const ::visual_servo::joint_positon_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace visual_servo

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::visual_servo::joint_positon_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::visual_servo::joint_positon_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::visual_servo::joint_positon_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::visual_servo::joint_positon_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::visual_servo::joint_positon_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::visual_servo::joint_positon_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::visual_servo::joint_positon_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a82fc01b03f66381c43297a78b5259f1";
  }

  static const char* value(const ::visual_servo::joint_positon_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa82fc01b03f66381ULL;
  static const uint64_t static_value2 = 0xc43297a78b5259f1ULL;
};

template<class ContainerAllocator>
struct DataType< ::visual_servo::joint_positon_<ContainerAllocator> >
{
  static const char* value()
  {
    return "visual_servo/joint_positon";
  }

  static const char* value(const ::visual_servo::joint_positon_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::visual_servo::joint_positon_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n"
"float32 shoulder_pan_joint\n"
"float32 shoulder_lift_joint\n"
"float32 elbow_joint\n"
"float32 wrist_1_joint\n"
"float32 wrist_2_joint\n"
"float32 wrist_3_joint\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::visual_servo::joint_positon_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::visual_servo::joint_positon_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.shoulder_pan_joint);
      stream.next(m.shoulder_lift_joint);
      stream.next(m.elbow_joint);
      stream.next(m.wrist_1_joint);
      stream.next(m.wrist_2_joint);
      stream.next(m.wrist_3_joint);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct joint_positon_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::visual_servo::joint_positon_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::visual_servo::joint_positon_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "shoulder_pan_joint: ";
    Printer<float>::stream(s, indent + "  ", v.shoulder_pan_joint);
    s << indent << "shoulder_lift_joint: ";
    Printer<float>::stream(s, indent + "  ", v.shoulder_lift_joint);
    s << indent << "elbow_joint: ";
    Printer<float>::stream(s, indent + "  ", v.elbow_joint);
    s << indent << "wrist_1_joint: ";
    Printer<float>::stream(s, indent + "  ", v.wrist_1_joint);
    s << indent << "wrist_2_joint: ";
    Printer<float>::stream(s, indent + "  ", v.wrist_2_joint);
    s << indent << "wrist_3_joint: ";
    Printer<float>::stream(s, indent + "  ", v.wrist_3_joint);
  }
};

} // namespace message_operations
} // namespace ros

#endif // VISUAL_SERVO_MESSAGE_JOINT_POSITON_H