// Generated by gencpp from file visp_camera_calibration/calibrate.msg
// DO NOT EDIT!


#ifndef VISP_CAMERA_CALIBRATION_MESSAGE_CALIBRATE_H
#define VISP_CAMERA_CALIBRATION_MESSAGE_CALIBRATE_H

#include <ros/service_traits.h>


#include <visp_camera_calibration/calibrateRequest.h>
#include <visp_camera_calibration/calibrateResponse.h>


namespace visp_camera_calibration
{

struct calibrate
{

typedef calibrateRequest Request;
typedef calibrateResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct calibrate
} // namespace visp_camera_calibration


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::visp_camera_calibration::calibrate > {
  static const char* value()
  {
    return "30e17d7747033ddb69c9980395e78d44";
  }

  static const char* value(const ::visp_camera_calibration::calibrate&) { return value(); }
};

template<>
struct DataType< ::visp_camera_calibration::calibrate > {
  static const char* value()
  {
    return "visp_camera_calibration/calibrate";
  }

  static const char* value(const ::visp_camera_calibration::calibrate&) { return value(); }
};


// service_traits::MD5Sum< ::visp_camera_calibration::calibrateRequest> should match
// service_traits::MD5Sum< ::visp_camera_calibration::calibrate >
template<>
struct MD5Sum< ::visp_camera_calibration::calibrateRequest>
{
  static const char* value()
  {
    return MD5Sum< ::visp_camera_calibration::calibrate >::value();
  }
  static const char* value(const ::visp_camera_calibration::calibrateRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::visp_camera_calibration::calibrateRequest> should match
// service_traits::DataType< ::visp_camera_calibration::calibrate >
template<>
struct DataType< ::visp_camera_calibration::calibrateRequest>
{
  static const char* value()
  {
    return DataType< ::visp_camera_calibration::calibrate >::value();
  }
  static const char* value(const ::visp_camera_calibration::calibrateRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::visp_camera_calibration::calibrateResponse> should match
// service_traits::MD5Sum< ::visp_camera_calibration::calibrate >
template<>
struct MD5Sum< ::visp_camera_calibration::calibrateResponse>
{
  static const char* value()
  {
    return MD5Sum< ::visp_camera_calibration::calibrate >::value();
  }
  static const char* value(const ::visp_camera_calibration::calibrateResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::visp_camera_calibration::calibrateResponse> should match
// service_traits::DataType< ::visp_camera_calibration::calibrate >
template<>
struct DataType< ::visp_camera_calibration::calibrateResponse>
{
  static const char* value()
  {
    return DataType< ::visp_camera_calibration::calibrate >::value();
  }
  static const char* value(const ::visp_camera_calibration::calibrateResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // VISP_CAMERA_CALIBRATION_MESSAGE_CALIBRATE_H