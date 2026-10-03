// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from orbbec_camera_msgs:msg/StreamProfile.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "orbbec_camera_msgs/msg/detail/stream_profile__rosidl_typesupport_introspection_c.h"
#include "orbbec_camera_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "orbbec_camera_msgs/msg/detail/stream_profile__functions.h"
#include "orbbec_camera_msgs/msg/detail/stream_profile__struct.h"


// Include directives for member types
// Member `stream_name`
// Member `format`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  orbbec_camera_msgs__msg__StreamProfile__init(message_memory);
}

void orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_fini_function(void * message_memory)
{
  orbbec_camera_msgs__msg__StreamProfile__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_message_member_array[5] = {
  {
    "stream_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(orbbec_camera_msgs__msg__StreamProfile, stream_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(orbbec_camera_msgs__msg__StreamProfile, width),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "height",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(orbbec_camera_msgs__msg__StreamProfile, height),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "fps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(orbbec_camera_msgs__msg__StreamProfile, fps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "format",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(orbbec_camera_msgs__msg__StreamProfile, format),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_message_members = {
  "orbbec_camera_msgs__msg",  // message namespace
  "StreamProfile",  // message name
  5,  // number of fields
  sizeof(orbbec_camera_msgs__msg__StreamProfile),
  orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_message_member_array,  // message members
  orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_init_function,  // function to initialize message memory (memory has to be allocated)
  orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_message_type_support_handle = {
  0,
  &orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_orbbec_camera_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, msg, StreamProfile)() {
  if (!orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_message_type_support_handle.typesupport_identifier) {
    orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &orbbec_camera_msgs__msg__StreamProfile__rosidl_typesupport_introspection_c__StreamProfile_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
