// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from orbbec_camera_msgs:srv/SetStreamProfile.idl
// generated code does not contain a copyright notice

#ifndef ORBBEC_CAMERA_MSGS__SRV__DETAIL__SET_STREAM_PROFILE__STRUCT_HPP_
#define ORBBEC_CAMERA_MSGS__SRV__DETAIL__SET_STREAM_PROFILE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'profiles'
#include "orbbec_camera_msgs/msg/detail/stream_profile__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__orbbec_camera_msgs__srv__SetStreamProfile_Request __attribute__((deprecated))
#else
# define DEPRECATED__orbbec_camera_msgs__srv__SetStreamProfile_Request __declspec(deprecated)
#endif

namespace orbbec_camera_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetStreamProfile_Request_
{
  using Type = SetStreamProfile_Request_<ContainerAllocator>;

  explicit SetStreamProfile_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SetStreamProfile_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _profiles_type =
    std::vector<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>>>;
  _profiles_type profiles;

  // setters for named parameter idiom
  Type & set__profiles(
    const std::vector<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<orbbec_camera_msgs::msg::StreamProfile_<ContainerAllocator>>> & _arg)
  {
    this->profiles = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__orbbec_camera_msgs__srv__SetStreamProfile_Request
    std::shared_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__orbbec_camera_msgs__srv__SetStreamProfile_Request
    std::shared_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetStreamProfile_Request_ & other) const
  {
    if (this->profiles != other.profiles) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetStreamProfile_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetStreamProfile_Request_

// alias to use template instance with default allocator
using SetStreamProfile_Request =
  orbbec_camera_msgs::srv::SetStreamProfile_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace orbbec_camera_msgs


#ifndef _WIN32
# define DEPRECATED__orbbec_camera_msgs__srv__SetStreamProfile_Response __attribute__((deprecated))
#else
# define DEPRECATED__orbbec_camera_msgs__srv__SetStreamProfile_Response __declspec(deprecated)
#endif

namespace orbbec_camera_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetStreamProfile_Response_
{
  using Type = SetStreamProfile_Response_<ContainerAllocator>;

  explicit SetStreamProfile_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetStreamProfile_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__orbbec_camera_msgs__srv__SetStreamProfile_Response
    std::shared_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__orbbec_camera_msgs__srv__SetStreamProfile_Response
    std::shared_ptr<orbbec_camera_msgs::srv::SetStreamProfile_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetStreamProfile_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetStreamProfile_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetStreamProfile_Response_

// alias to use template instance with default allocator
using SetStreamProfile_Response =
  orbbec_camera_msgs::srv::SetStreamProfile_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace orbbec_camera_msgs

namespace orbbec_camera_msgs
{

namespace srv
{

struct SetStreamProfile
{
  using Request = orbbec_camera_msgs::srv::SetStreamProfile_Request;
  using Response = orbbec_camera_msgs::srv::SetStreamProfile_Response;
};

}  // namespace srv

}  // namespace orbbec_camera_msgs

#endif  // ORBBEC_CAMERA_MSGS__SRV__DETAIL__SET_STREAM_PROFILE__STRUCT_HPP_
