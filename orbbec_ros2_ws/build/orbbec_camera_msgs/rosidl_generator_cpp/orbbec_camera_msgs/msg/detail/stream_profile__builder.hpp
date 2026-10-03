// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from orbbec_camera_msgs:msg/StreamProfile.idl
// generated code does not contain a copyright notice

#ifndef ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__BUILDER_HPP_
#define ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "orbbec_camera_msgs/msg/detail/stream_profile__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace orbbec_camera_msgs
{

namespace msg
{

namespace builder
{

class Init_StreamProfile_format
{
public:
  explicit Init_StreamProfile_format(::orbbec_camera_msgs::msg::StreamProfile & msg)
  : msg_(msg)
  {}
  ::orbbec_camera_msgs::msg::StreamProfile format(::orbbec_camera_msgs::msg::StreamProfile::_format_type arg)
  {
    msg_.format = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orbbec_camera_msgs::msg::StreamProfile msg_;
};

class Init_StreamProfile_fps
{
public:
  explicit Init_StreamProfile_fps(::orbbec_camera_msgs::msg::StreamProfile & msg)
  : msg_(msg)
  {}
  Init_StreamProfile_format fps(::orbbec_camera_msgs::msg::StreamProfile::_fps_type arg)
  {
    msg_.fps = std::move(arg);
    return Init_StreamProfile_format(msg_);
  }

private:
  ::orbbec_camera_msgs::msg::StreamProfile msg_;
};

class Init_StreamProfile_height
{
public:
  explicit Init_StreamProfile_height(::orbbec_camera_msgs::msg::StreamProfile & msg)
  : msg_(msg)
  {}
  Init_StreamProfile_fps height(::orbbec_camera_msgs::msg::StreamProfile::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_StreamProfile_fps(msg_);
  }

private:
  ::orbbec_camera_msgs::msg::StreamProfile msg_;
};

class Init_StreamProfile_width
{
public:
  explicit Init_StreamProfile_width(::orbbec_camera_msgs::msg::StreamProfile & msg)
  : msg_(msg)
  {}
  Init_StreamProfile_height width(::orbbec_camera_msgs::msg::StreamProfile::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_StreamProfile_height(msg_);
  }

private:
  ::orbbec_camera_msgs::msg::StreamProfile msg_;
};

class Init_StreamProfile_stream_name
{
public:
  Init_StreamProfile_stream_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StreamProfile_width stream_name(::orbbec_camera_msgs::msg::StreamProfile::_stream_name_type arg)
  {
    msg_.stream_name = std::move(arg);
    return Init_StreamProfile_width(msg_);
  }

private:
  ::orbbec_camera_msgs::msg::StreamProfile msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::orbbec_camera_msgs::msg::StreamProfile>()
{
  return orbbec_camera_msgs::msg::builder::Init_StreamProfile_stream_name();
}

}  // namespace orbbec_camera_msgs

#endif  // ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__BUILDER_HPP_
