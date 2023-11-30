// Generated by gencpp from file visual_servo/pbvs_circles.msg
// DO NOT EDIT!


#ifndef VISUAL_SERVO_MESSAGE_PBVS_CIRCLES_H
#define VISUAL_SERVO_MESSAGE_PBVS_CIRCLES_H


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
struct pbvs_circles_
{
  typedef pbvs_circles_<ContainerAllocator> Type;

  pbvs_circles_()
    : header()
    , circle1()
    , circle2()
    , circle3()
    , circle4()  {
      circle1.assign(0.0);

      circle2.assign(0.0);

      circle3.assign(0.0);

      circle4.assign(0.0);
  }
  pbvs_circles_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , circle1()
    , circle2()
    , circle3()
    , circle4()  {
  (void)_alloc;
      circle1.assign(0.0);

      circle2.assign(0.0);

      circle3.assign(0.0);

      circle4.assign(0.0);
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef boost::array<float, 3>  _circle1_type;
  _circle1_type circle1;

   typedef boost::array<float, 3>  _circle2_type;
  _circle2_type circle2;

   typedef boost::array<float, 3>  _circle3_type;
  _circle3_type circle3;

   typedef boost::array<float, 3>  _circle4_type;
  _circle4_type circle4;





  typedef boost::shared_ptr< ::visual_servo::pbvs_circles_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::visual_servo::pbvs_circles_<ContainerAllocator> const> ConstPtr;

}; // struct pbvs_circles_

typedef ::visual_servo::pbvs_circles_<std::allocator<void> > pbvs_circles;

typedef boost::shared_ptr< ::visual_servo::pbvs_circles > pbvs_circlesPtr;
typedef boost::shared_ptr< ::visual_servo::pbvs_circles const> pbvs_circlesConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::visual_servo::pbvs_circles_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::visual_servo::pbvs_circles_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::visual_servo::pbvs_circles_<ContainerAllocator1> & lhs, const ::visual_servo::pbvs_circles_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.circle1 == rhs.circle1 &&
    lhs.circle2 == rhs.circle2 &&
    lhs.circle3 == rhs.circle3 &&
    lhs.circle4 == rhs.circle4;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::visual_servo::pbvs_circles_<ContainerAllocator1> & lhs, const ::visual_servo::pbvs_circles_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace visual_servo

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::visual_servo::pbvs_circles_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::visual_servo::pbvs_circles_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::visual_servo::pbvs_circles_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::visual_servo::pbvs_circles_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::visual_servo::pbvs_circles_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::visual_servo::pbvs_circles_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::visual_servo::pbvs_circles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f98297f55b162ac720ff220dc219f92d";
  }

  static const char* value(const ::visual_servo::pbvs_circles_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf98297f55b162ac7ULL;
  static const uint64_t static_value2 = 0x20ff220dc219f92dULL;
};

template<class ContainerAllocator>
struct DataType< ::visual_servo::pbvs_circles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "visual_servo/pbvs_circles";
  }

  static const char* value(const ::visual_servo::pbvs_circles_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::visual_servo::pbvs_circles_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n"
"float32[3] circle1\n"
"float32[3] circle2\n"
"float32[3] circle3\n"
"float32[3] circle4\n"
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

  static const char* value(const ::visual_servo::pbvs_circles_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::visual_servo::pbvs_circles_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.circle1);
      stream.next(m.circle2);
      stream.next(m.circle3);
      stream.next(m.circle4);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct pbvs_circles_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::visual_servo::pbvs_circles_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::visual_servo::pbvs_circles_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "circle1[]" << std::endl;
    for (size_t i = 0; i < v.circle1.size(); ++i)
    {
      s << indent << "  circle1[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.circle1[i]);
    }
    s << indent << "circle2[]" << std::endl;
    for (size_t i = 0; i < v.circle2.size(); ++i)
    {
      s << indent << "  circle2[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.circle2[i]);
    }
    s << indent << "circle3[]" << std::endl;
    for (size_t i = 0; i < v.circle3.size(); ++i)
    {
      s << indent << "  circle3[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.circle3[i]);
    }
    s << indent << "circle4[]" << std::endl;
    for (size_t i = 0; i < v.circle4.size(); ++i)
    {
      s << indent << "  circle4[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.circle4[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // VISUAL_SERVO_MESSAGE_PBVS_CIRCLES_H