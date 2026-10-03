// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from orbbec_camera_msgs:msg/StreamProfile.idl
// generated code does not contain a copyright notice
#include "orbbec_camera_msgs/msg/detail/stream_profile__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stream_name`
// Member `format`
#include "rosidl_runtime_c/string_functions.h"

bool
orbbec_camera_msgs__msg__StreamProfile__init(orbbec_camera_msgs__msg__StreamProfile * msg)
{
  if (!msg) {
    return false;
  }
  // stream_name
  if (!rosidl_runtime_c__String__init(&msg->stream_name)) {
    orbbec_camera_msgs__msg__StreamProfile__fini(msg);
    return false;
  }
  // width
  // height
  // fps
  // format
  if (!rosidl_runtime_c__String__init(&msg->format)) {
    orbbec_camera_msgs__msg__StreamProfile__fini(msg);
    return false;
  }
  return true;
}

void
orbbec_camera_msgs__msg__StreamProfile__fini(orbbec_camera_msgs__msg__StreamProfile * msg)
{
  if (!msg) {
    return;
  }
  // stream_name
  rosidl_runtime_c__String__fini(&msg->stream_name);
  // width
  // height
  // fps
  // format
  rosidl_runtime_c__String__fini(&msg->format);
}

bool
orbbec_camera_msgs__msg__StreamProfile__are_equal(const orbbec_camera_msgs__msg__StreamProfile * lhs, const orbbec_camera_msgs__msg__StreamProfile * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stream_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->stream_name), &(rhs->stream_name)))
  {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  // fps
  if (lhs->fps != rhs->fps) {
    return false;
  }
  // format
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->format), &(rhs->format)))
  {
    return false;
  }
  return true;
}

bool
orbbec_camera_msgs__msg__StreamProfile__copy(
  const orbbec_camera_msgs__msg__StreamProfile * input,
  orbbec_camera_msgs__msg__StreamProfile * output)
{
  if (!input || !output) {
    return false;
  }
  // stream_name
  if (!rosidl_runtime_c__String__copy(
      &(input->stream_name), &(output->stream_name)))
  {
    return false;
  }
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  // fps
  output->fps = input->fps;
  // format
  if (!rosidl_runtime_c__String__copy(
      &(input->format), &(output->format)))
  {
    return false;
  }
  return true;
}

orbbec_camera_msgs__msg__StreamProfile *
orbbec_camera_msgs__msg__StreamProfile__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orbbec_camera_msgs__msg__StreamProfile * msg = (orbbec_camera_msgs__msg__StreamProfile *)allocator.allocate(sizeof(orbbec_camera_msgs__msg__StreamProfile), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(orbbec_camera_msgs__msg__StreamProfile));
  bool success = orbbec_camera_msgs__msg__StreamProfile__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
orbbec_camera_msgs__msg__StreamProfile__destroy(orbbec_camera_msgs__msg__StreamProfile * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    orbbec_camera_msgs__msg__StreamProfile__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
orbbec_camera_msgs__msg__StreamProfile__Sequence__init(orbbec_camera_msgs__msg__StreamProfile__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orbbec_camera_msgs__msg__StreamProfile * data = NULL;

  if (size) {
    data = (orbbec_camera_msgs__msg__StreamProfile *)allocator.zero_allocate(size, sizeof(orbbec_camera_msgs__msg__StreamProfile), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = orbbec_camera_msgs__msg__StreamProfile__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        orbbec_camera_msgs__msg__StreamProfile__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
orbbec_camera_msgs__msg__StreamProfile__Sequence__fini(orbbec_camera_msgs__msg__StreamProfile__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      orbbec_camera_msgs__msg__StreamProfile__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

orbbec_camera_msgs__msg__StreamProfile__Sequence *
orbbec_camera_msgs__msg__StreamProfile__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orbbec_camera_msgs__msg__StreamProfile__Sequence * array = (orbbec_camera_msgs__msg__StreamProfile__Sequence *)allocator.allocate(sizeof(orbbec_camera_msgs__msg__StreamProfile__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = orbbec_camera_msgs__msg__StreamProfile__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
orbbec_camera_msgs__msg__StreamProfile__Sequence__destroy(orbbec_camera_msgs__msg__StreamProfile__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    orbbec_camera_msgs__msg__StreamProfile__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
orbbec_camera_msgs__msg__StreamProfile__Sequence__are_equal(const orbbec_camera_msgs__msg__StreamProfile__Sequence * lhs, const orbbec_camera_msgs__msg__StreamProfile__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!orbbec_camera_msgs__msg__StreamProfile__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
orbbec_camera_msgs__msg__StreamProfile__Sequence__copy(
  const orbbec_camera_msgs__msg__StreamProfile__Sequence * input,
  orbbec_camera_msgs__msg__StreamProfile__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(orbbec_camera_msgs__msg__StreamProfile);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    orbbec_camera_msgs__msg__StreamProfile * data =
      (orbbec_camera_msgs__msg__StreamProfile *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!orbbec_camera_msgs__msg__StreamProfile__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          orbbec_camera_msgs__msg__StreamProfile__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!orbbec_camera_msgs__msg__StreamProfile__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
