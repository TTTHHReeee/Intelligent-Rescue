// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from orbbec_camera_msgs:msg/StreamProfile.idl
// generated code does not contain a copyright notice

#ifndef ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__TRAITS_HPP_
#define ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "orbbec_camera_msgs/msg/detail/stream_profile__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace orbbec_camera_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const StreamProfile & msg,
  std::ostream & out)
{
  out << "{";
  // member: stream_name
  {
    out << "stream_name: ";
    rosidl_generator_traits::value_to_yaml(msg.stream_name, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << ", ";
  }

  // member: height
  {
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << ", ";
  }

  // member: fps
  {
    out << "fps: ";
    rosidl_generator_traits::value_to_yaml(msg.fps, out);
    out << ", ";
  }

  // member: format
  {
    out << "format: ";
    rosidl_generator_traits::value_to_yaml(msg.format, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StreamProfile & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stream_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stream_name: ";
    rosidl_generator_traits::value_to_yaml(msg.stream_name, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << "\n";
  }

  // member: fps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fps: ";
    rosidl_generator_traits::value_to_yaml(msg.fps, out);
    out << "\n";
  }

  // member: format
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "format: ";
    rosidl_generator_traits::value_to_yaml(msg.format, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StreamProfile & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace orbbec_camera_msgs

namespace rosidl_generator_traits
{

[[deprecated("use orbbec_camera_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const orbbec_camera_msgs::msg::StreamProfile & msg,
  std::ostream & out, size_t indentation = 0)
{
  orbbec_camera_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use orbbec_camera_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const orbbec_camera_msgs::msg::StreamProfile & msg)
{
  return orbbec_camera_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<orbbec_camera_msgs::msg::StreamProfile>()
{
  return "orbbec_camera_msgs::msg::StreamProfile";
}

template<>
inline const char * name<orbbec_camera_msgs::msg::StreamProfile>()
{
  return "orbbec_camera_msgs/msg/StreamProfile";
}

template<>
struct has_fixed_size<orbbec_camera_msgs::msg::StreamProfile>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<orbbec_camera_msgs::msg::StreamProfile>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<orbbec_camera_msgs::msg::StreamProfile>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__TRAITS_HPP_
