// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from orbbec_camera_msgs:srv/SetStreamProfile.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "orbbec_camera_msgs/srv/detail/set_stream_profile__rosidl_typesupport_introspection_c.h"
#include "orbbec_camera_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "orbbec_camera_msgs/srv/detail/set_stream_profile__functions.h"
#include "orbbec_camera_msgs/srv/detail/set_stream_profile__struct.h"


// Include directives for member types
// Member `profiles`
#include "orbbec_camera_msgs/msg/stream_profile.h"
// Member `profiles`
#include "orbbec_camera_msgs/msg/detail/stream_profile__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  orbbec_camera_msgs__srv__SetStreamProfile_Request__init(message_memory);
}

void orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_fini_function(void * message_memory)
{
  orbbec_camera_msgs__srv__SetStreamProfile_Request__fini(message_memory);
}

size_t orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__size_function__SetStreamProfile_Request__profiles(
  const void * untyped_member)
{
  const orbbec_camera_msgs__msg__StreamProfile__Sequence * member =
    (const orbbec_camera_msgs__msg__StreamProfile__Sequence *)(untyped_member);
  return member->size;
}

const void * orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetStreamProfile_Request__profiles(
  const void * untyped_member, size_t index)
{
  const orbbec_camera_msgs__msg__StreamProfile__Sequence * member =
    (const orbbec_camera_msgs__msg__StreamProfile__Sequence *)(untyped_member);
  return &member->data[index];
}

void * orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__get_function__SetStreamProfile_Request__profiles(
  void * untyped_member, size_t index)
{
  orbbec_camera_msgs__msg__StreamProfile__Sequence * member =
    (orbbec_camera_msgs__msg__StreamProfile__Sequence *)(untyped_member);
  return &member->data[index];
}

void orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__fetch_function__SetStreamProfile_Request__profiles(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const orbbec_camera_msgs__msg__StreamProfile * item =
    ((const orbbec_camera_msgs__msg__StreamProfile *)
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetStreamProfile_Request__profiles(untyped_member, index));
  orbbec_camera_msgs__msg__StreamProfile * value =
    (orbbec_camera_msgs__msg__StreamProfile *)(untyped_value);
  *value = *item;
}

void orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__assign_function__SetStreamProfile_Request__profiles(
  void * untyped_member, size_t index, const void * untyped_value)
{
  orbbec_camera_msgs__msg__StreamProfile * item =
    ((orbbec_camera_msgs__msg__StreamProfile *)
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__get_function__SetStreamProfile_Request__profiles(untyped_member, index));
  const orbbec_camera_msgs__msg__StreamProfile * value =
    (const orbbec_camera_msgs__msg__StreamProfile *)(untyped_value);
  *item = *value;
}

bool orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__resize_function__SetStreamProfile_Request__profiles(
  void * untyped_member, size_t size)
{
  orbbec_camera_msgs__msg__StreamProfile__Sequence * member =
    (orbbec_camera_msgs__msg__StreamProfile__Sequence *)(untyped_member);
  orbbec_camera_msgs__msg__StreamProfile__Sequence__fini(member);
  return orbbec_camera_msgs__msg__StreamProfile__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_member_array[1] = {
  {
    "profiles",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(orbbec_camera_msgs__srv__SetStreamProfile_Request, profiles),  // bytes offset in struct
    NULL,  // default value
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__size_function__SetStreamProfile_Request__profiles,  // size() function pointer
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__get_const_function__SetStreamProfile_Request__profiles,  // get_const(index) function pointer
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__get_function__SetStreamProfile_Request__profiles,  // get(index) function pointer
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__fetch_function__SetStreamProfile_Request__profiles,  // fetch(index, &value) function pointer
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__assign_function__SetStreamProfile_Request__profiles,  // assign(index, value) function pointer
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__resize_function__SetStreamProfile_Request__profiles  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_members = {
  "orbbec_camera_msgs__srv",  // message namespace
  "SetStreamProfile_Request",  // message name
  1,  // number of fields
  sizeof(orbbec_camera_msgs__srv__SetStreamProfile_Request),
  orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_member_array,  // message members
  orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_type_support_handle = {
  0,
  &orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_orbbec_camera_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, srv, SetStreamProfile_Request)() {
  orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, msg, StreamProfile)();
  if (!orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_type_support_handle.typesupport_identifier) {
    orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &orbbec_camera_msgs__srv__SetStreamProfile_Request__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "orbbec_camera_msgs/srv/detail/set_stream_profile__rosidl_typesupport_introspection_c.h"
// already included above
// #include "orbbec_camera_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "orbbec_camera_msgs/srv/detail/set_stream_profile__functions.h"
// already included above
// #include "orbbec_camera_msgs/srv/detail/set_stream_profile__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  orbbec_camera_msgs__srv__SetStreamProfile_Response__init(message_memory);
}

void orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_fini_function(void * message_memory)
{
  orbbec_camera_msgs__srv__SetStreamProfile_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(orbbec_camera_msgs__srv__SetStreamProfile_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(orbbec_camera_msgs__srv__SetStreamProfile_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_members = {
  "orbbec_camera_msgs__srv",  // message namespace
  "SetStreamProfile_Response",  // message name
  2,  // number of fields
  sizeof(orbbec_camera_msgs__srv__SetStreamProfile_Response),
  orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_member_array,  // message members
  orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_type_support_handle = {
  0,
  &orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_orbbec_camera_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, srv, SetStreamProfile_Response)() {
  if (!orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_type_support_handle.typesupport_identifier) {
    orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &orbbec_camera_msgs__srv__SetStreamProfile_Response__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "orbbec_camera_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "orbbec_camera_msgs/srv/detail/set_stream_profile__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_service_members = {
  "orbbec_camera_msgs__srv",  // service namespace
  "SetStreamProfile",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_Request_message_type_support_handle,
  NULL  // response message
  // orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_Response_message_type_support_handle
};

static rosidl_service_type_support_t orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_service_type_support_handle = {
  0,
  &orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, srv, SetStreamProfile_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, srv, SetStreamProfile_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_orbbec_camera_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, srv, SetStreamProfile)() {
  if (!orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_service_type_support_handle.typesupport_identifier) {
    orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, srv, SetStreamProfile_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, orbbec_camera_msgs, srv, SetStreamProfile_Response)()->data;
  }

  return &orbbec_camera_msgs__srv__detail__set_stream_profile__rosidl_typesupport_introspection_c__SetStreamProfile_service_type_support_handle;
}
