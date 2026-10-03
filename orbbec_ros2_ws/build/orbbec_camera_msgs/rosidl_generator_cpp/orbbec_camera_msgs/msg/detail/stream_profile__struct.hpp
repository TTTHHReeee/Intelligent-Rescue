// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from orbbec_camera_msgs:msg/StreamProfile.idl
// generated code does not contain a copyright notice

#ifndef ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__STRUCT_HPP_
#define ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__orbbec_camera_msgs__msg__StreamProfile __attribute__((deprecated))
#else
# define DEPRECATED__orbbec_camera_msgs__msg__StreamProfile __declspec(deprecated)
#endif

namespace orbbec_camera_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct StreamProfile_
{
  using Type = StreamProfile_<ContainerAllocator>;

  explicit StreamProfile_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stream_name = "";
      this->width = 0l;
      this->height = 0l;
      this->fps = 0l;
      this->format = "";
    }
  }

  explicit StreamProfile_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stream_name(_alloc),
    format(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stream_name = "";
      this->width = 0l;
      this->height = 0l;
      this->fps = 0l;
      this->format = "";
    }
  }

  // field types and members
  using _stream_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _stream_name_type stream_name;
  using _width_type =
    int32_t;
  _width_type width;
  using _height_type =
    int32_t;
  _height_type height;
  using _fps_type =
    int32_t;
  _fps_type fps;
  using _format_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _format_type format;

  // setters for named parameter idiom
  Type & set__stream_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->stream_name = _arg;
    return *this;
  }
  Type & set__width(
    const int32_t & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__height(
    const int32_t & _arg)
  {
    this->height = _arg;
    return *this;
  }
  Type & set__fps(
    const int32_t & _arg)
  {
    this->fps = _arg;
    return *this;
  }
  Type & set__format(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->format = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator> *;
  using ConstRawPtr =
    const orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__orbbec_camera_msgs__msg__StreamProfile
    std::shared_ptr<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__orbbec_camera_msgs__msg__StreamProfile
    std::shared_ptr<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StreamProfile_ & other) const
  {
    if (this->stream_name != other.stream_name) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    if (this->fps != other.fps) {
      return false;
    }
    if (this->format != other.format) {
      return false;
    }
    return true;
  }
  bool operator!=(const StreamProfile_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StreamProfile_

// alias to use template instance with default allocator
using StreamProfile =
  orbbec_camera_msgs::msg::StreamProfile_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace orbbec_camera_msgs

#endif  // ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__STRUCT_HPP_
