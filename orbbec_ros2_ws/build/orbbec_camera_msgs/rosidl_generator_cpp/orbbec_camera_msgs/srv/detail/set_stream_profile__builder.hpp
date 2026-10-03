// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from orbbec_camera_msgs:srv/SetStreamProfile.idl
// generated code does not contain a copyright notice

#ifndef ORBBEC_CAMERA_MSGS__SRV__DETAIL__SET_STREAM_PROFILE__BUILDER_HPP_
#define ORBBEC_CAMERA_MSGS__SRV__DETAIL__SET_STREAM_PROFILE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "orbbec_camera_msgs/srv/detail/set_stream_profile__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace orbbec_camera_msgs
{

namespace srv
{

namespace builder
{

class Init_SetStreamProfile_Request_profiles
{
public:
  Init_SetStreamProfile_Request_profiles()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::orbbec_camera_msgs::srv::SetStreamProfile_Request profiles(::orbbec_camera_msgs::srv::SetStreamProfile_Request::_profiles_type arg)
  {
    msg_.profiles = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orbbec_camera_msgs::srv::SetStreamProfile_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::orbbec_camera_msgs::srv::SetStreamProfile_Request>()
{
  return orbbec_camera_msgs::srv::builder::Init_SetStreamProfile_Request_profiles();
}

}  // namespace orbbec_camera_msgs


namespace orbbec_camera_msgs
{

namespace srv
{

namespace builder
{

class Init_SetStreamProfile_Response_message
{
public:
  explicit Init_SetStreamProfile_Response_message(::orbbec_camera_msgs::srv::SetStreamProfile_Response & msg)
  : msg_(msg)
  {}
  ::orbbec_camera_msgs::srv::SetStreamProfile_Response message(::orbbec_camera_msgs::srv::SetStreamProfile_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orbbec_camera_msgs::srv::SetStreamProfile_Response msg_;
};

class Init_SetStreamProfile_Response_success
{
public:
  Init_SetStreamProfile_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetStreamProfile_Response_message success(::orbbec_camera_msgs::srv::SetStreamProfile_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetStreamProfile_Response_message(msg_);
  }

private:
  ::orbbec_camera_msgs::srv::SetStreamProfile_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::orbbec_camera_msgs::srv::SetStreamProfile_Response>()
{
  return orbbec_camera_msgs::srv::builder::Init_SetStreamProfile_Response_success();
}

}  // namespace orbbec_camera_msgs

#endif  // ORBBEC_CAMERA_MSGS__SRV__DETAIL__SET_STREAM_PROFILE__BUILDER_HPP_
