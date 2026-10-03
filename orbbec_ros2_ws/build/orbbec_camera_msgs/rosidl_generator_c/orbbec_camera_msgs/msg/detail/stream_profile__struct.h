// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from orbbec_camera_msgs:msg/StreamProfile.idl
// generated code does not contain a copyright notice

#ifndef ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__STRUCT_H_
#define ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stream_name'
// Member 'format'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/StreamProfile in the package orbbec_camera_msgs.
typedef struct orbbec_camera_msgs__msg__StreamProfile
{
  rosidl_runtime_c__String stream_name;
  int32_t width;
  int32_t height;
  int32_t fps;
  rosidl_runtime_c__String format;
} orbbec_camera_msgs__msg__StreamProfile;

// Struct for a sequence of orbbec_camera_msgs__msg__StreamProfile.
typedef struct orbbec_camera_msgs__msg__StreamProfile__Sequence
{
  orbbec_camera_msgs__msg__StreamProfile * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} orbbec_camera_msgs__msg__StreamProfile__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ORBBEC_CAMERA_MSGS__MSG__DETAIL__STREAM_PROFILE__STRUCT_H_
