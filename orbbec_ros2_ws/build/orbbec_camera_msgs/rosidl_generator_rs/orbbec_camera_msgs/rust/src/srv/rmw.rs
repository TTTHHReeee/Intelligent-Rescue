#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetBool_Request() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetBool_Request__init(msg: *mut GetBool_Request) -> bool;
    fn orbbec_camera_msgs__srv__GetBool_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetBool_Request>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetBool_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetBool_Request>);
    fn orbbec_camera_msgs__srv__GetBool_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetBool_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetBool_Request>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetBool_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetBool_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetBool_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetBool_Request__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetBool_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetBool_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetBool_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetBool_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetBool_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetBool_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetBool_Request where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetBool_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetBool_Request() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetBool_Response() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetBool_Response__init(msg: *mut GetBool_Response) -> bool;
    fn orbbec_camera_msgs__srv__GetBool_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetBool_Response>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetBool_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetBool_Response>);
    fn orbbec_camera_msgs__srv__GetBool_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetBool_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetBool_Response>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetBool_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetBool_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub data: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for GetBool_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetBool_Response__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetBool_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetBool_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetBool_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetBool_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetBool_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetBool_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetBool_Response where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetBool_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetBool_Response() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetDeviceInfo_Request() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetDeviceInfo_Request__init(msg: *mut GetDeviceInfo_Request) -> bool;
    fn orbbec_camera_msgs__srv__GetDeviceInfo_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetDeviceInfo_Request>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetDeviceInfo_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetDeviceInfo_Request>);
    fn orbbec_camera_msgs__srv__GetDeviceInfo_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetDeviceInfo_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetDeviceInfo_Request>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetDeviceInfo_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetDeviceInfo_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetDeviceInfo_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetDeviceInfo_Request__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetDeviceInfo_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetDeviceInfo_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetDeviceInfo_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetDeviceInfo_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetDeviceInfo_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetDeviceInfo_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetDeviceInfo_Request where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetDeviceInfo_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetDeviceInfo_Request() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetDeviceInfo_Response() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetDeviceInfo_Response__init(msg: *mut GetDeviceInfo_Response) -> bool;
    fn orbbec_camera_msgs__srv__GetDeviceInfo_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetDeviceInfo_Response>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetDeviceInfo_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetDeviceInfo_Response>);
    fn orbbec_camera_msgs__srv__GetDeviceInfo_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetDeviceInfo_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetDeviceInfo_Response>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetDeviceInfo_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetDeviceInfo_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub info: super::super::msg::rmw::DeviceInfo,


    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for GetDeviceInfo_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetDeviceInfo_Response__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetDeviceInfo_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetDeviceInfo_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetDeviceInfo_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetDeviceInfo_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetDeviceInfo_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetDeviceInfo_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetDeviceInfo_Response where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetDeviceInfo_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetDeviceInfo_Response() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetCameraInfo_Request() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetCameraInfo_Request__init(msg: *mut GetCameraInfo_Request) -> bool;
    fn orbbec_camera_msgs__srv__GetCameraInfo_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetCameraInfo_Request>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetCameraInfo_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetCameraInfo_Request>);
    fn orbbec_camera_msgs__srv__GetCameraInfo_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetCameraInfo_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetCameraInfo_Request>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetCameraInfo_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetCameraInfo_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetCameraInfo_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetCameraInfo_Request__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetCameraInfo_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetCameraInfo_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetCameraInfo_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetCameraInfo_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetCameraInfo_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetCameraInfo_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetCameraInfo_Request where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetCameraInfo_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetCameraInfo_Request() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetCameraInfo_Response() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetCameraInfo_Response__init(msg: *mut GetCameraInfo_Response) -> bool;
    fn orbbec_camera_msgs__srv__GetCameraInfo_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetCameraInfo_Response>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetCameraInfo_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetCameraInfo_Response>);
    fn orbbec_camera_msgs__srv__GetCameraInfo_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetCameraInfo_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetCameraInfo_Response>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetCameraInfo_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetCameraInfo_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub info: sensor_msgs::msg::rmw::CameraInfo,

}



impl Default for GetCameraInfo_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetCameraInfo_Response__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetCameraInfo_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetCameraInfo_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetCameraInfo_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetCameraInfo_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetCameraInfo_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetCameraInfo_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetCameraInfo_Response where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetCameraInfo_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetCameraInfo_Response() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetInt32_Request() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetInt32_Request__init(msg: *mut GetInt32_Request) -> bool;
    fn orbbec_camera_msgs__srv__GetInt32_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetInt32_Request>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetInt32_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetInt32_Request>);
    fn orbbec_camera_msgs__srv__GetInt32_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetInt32_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetInt32_Request>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetInt32_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetInt32_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetInt32_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetInt32_Request__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetInt32_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetInt32_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetInt32_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetInt32_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetInt32_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetInt32_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetInt32_Request where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetInt32_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetInt32_Request() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetInt32_Response() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetInt32_Response__init(msg: *mut GetInt32_Response) -> bool;
    fn orbbec_camera_msgs__srv__GetInt32_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetInt32_Response>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetInt32_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetInt32_Response>);
    fn orbbec_camera_msgs__srv__GetInt32_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetInt32_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetInt32_Response>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetInt32_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetInt32_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub data: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for GetInt32_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetInt32_Response__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetInt32_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetInt32_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetInt32_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetInt32_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetInt32_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetInt32_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetInt32_Response where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetInt32_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetInt32_Response() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetString_Request() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetString_Request__init(msg: *mut GetString_Request) -> bool;
    fn orbbec_camera_msgs__srv__GetString_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetString_Request>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetString_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetString_Request>);
    fn orbbec_camera_msgs__srv__GetString_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetString_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetString_Request>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetString_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetString_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetString_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetString_Request__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetString_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetString_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetString_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetString_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetString_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetString_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetString_Request where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetString_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetString_Request() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetString_Response() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__GetString_Response__init(msg: *mut GetString_Response) -> bool;
    fn orbbec_camera_msgs__srv__GetString_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetString_Response>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__GetString_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetString_Response>);
    fn orbbec_camera_msgs__srv__GetString_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetString_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetString_Response>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__GetString_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetString_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub data: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for GetString_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__GetString_Response__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__GetString_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetString_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetString_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetString_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__GetString_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetString_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetString_Response where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/GetString_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__GetString_Response() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetInt32_Request() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__SetInt32_Request__init(msg: *mut SetInt32_Request) -> bool;
    fn orbbec_camera_msgs__srv__SetInt32_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetInt32_Request>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__SetInt32_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetInt32_Request>);
    fn orbbec_camera_msgs__srv__SetInt32_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetInt32_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetInt32_Request>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__SetInt32_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetInt32_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub data: i32,

}



impl Default for SetInt32_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__SetInt32_Request__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__SetInt32_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetInt32_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetInt32_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetInt32_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetInt32_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetInt32_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetInt32_Request where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/SetInt32_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetInt32_Request() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetInt32_Response() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__SetInt32_Response__init(msg: *mut SetInt32_Response) -> bool;
    fn orbbec_camera_msgs__srv__SetInt32_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetInt32_Response>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__SetInt32_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetInt32_Response>);
    fn orbbec_camera_msgs__srv__SetInt32_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetInt32_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetInt32_Response>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__SetInt32_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetInt32_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for SetInt32_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__SetInt32_Response__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__SetInt32_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetInt32_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetInt32_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetInt32_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetInt32_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetInt32_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetInt32_Response where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/SetInt32_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetInt32_Response() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetString_Request() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__SetString_Request__init(msg: *mut SetString_Request) -> bool;
    fn orbbec_camera_msgs__srv__SetString_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetString_Request>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__SetString_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetString_Request>);
    fn orbbec_camera_msgs__srv__SetString_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetString_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetString_Request>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__SetString_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetString_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub data: rosidl_runtime_rs::String,

}



impl Default for SetString_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__SetString_Request__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__SetString_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetString_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetString_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetString_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetString_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetString_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetString_Request where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/SetString_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetString_Request() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetString_Response() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__SetString_Response__init(msg: *mut SetString_Response) -> bool;
    fn orbbec_camera_msgs__srv__SetString_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetString_Response>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__SetString_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetString_Response>);
    fn orbbec_camera_msgs__srv__SetString_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetString_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetString_Response>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__SetString_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetString_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for SetString_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__SetString_Response__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__SetString_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetString_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetString_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetString_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetString_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetString_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetString_Response where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/SetString_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetString_Response() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetStreamProfile_Request() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__SetStreamProfile_Request__init(msg: *mut SetStreamProfile_Request) -> bool;
    fn orbbec_camera_msgs__srv__SetStreamProfile_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetStreamProfile_Request>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__SetStreamProfile_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetStreamProfile_Request>);
    fn orbbec_camera_msgs__srv__SetStreamProfile_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetStreamProfile_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetStreamProfile_Request>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__SetStreamProfile_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetStreamProfile_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub profiles: rosidl_runtime_rs::Sequence<super::super::msg::rmw::StreamProfile>,

}



impl Default for SetStreamProfile_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__SetStreamProfile_Request__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__SetStreamProfile_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetStreamProfile_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetStreamProfile_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetStreamProfile_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetStreamProfile_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetStreamProfile_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetStreamProfile_Request where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/SetStreamProfile_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetStreamProfile_Request() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetStreamProfile_Response() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__srv__SetStreamProfile_Response__init(msg: *mut SetStreamProfile_Response) -> bool;
    fn orbbec_camera_msgs__srv__SetStreamProfile_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetStreamProfile_Response>, size: usize) -> bool;
    fn orbbec_camera_msgs__srv__SetStreamProfile_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetStreamProfile_Response>);
    fn orbbec_camera_msgs__srv__SetStreamProfile_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetStreamProfile_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetStreamProfile_Response>) -> bool;
}

// Corresponds to orbbec_camera_msgs__srv__SetStreamProfile_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetStreamProfile_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for SetStreamProfile_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__srv__SetStreamProfile_Response__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__srv__SetStreamProfile_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetStreamProfile_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetStreamProfile_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetStreamProfile_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__srv__SetStreamProfile_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetStreamProfile_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetStreamProfile_Response where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/srv/SetStreamProfile_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__srv__SetStreamProfile_Response() }
  }
}






#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetBool() -> *const std::ffi::c_void;
}

// Corresponds to orbbec_camera_msgs__srv__GetBool
#[allow(missing_docs, non_camel_case_types)]
pub struct GetBool;

impl rosidl_runtime_rs::Service for GetBool {
    type Request = GetBool_Request;
    type Response = GetBool_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetBool() }
    }
}




#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetDeviceInfo() -> *const std::ffi::c_void;
}

// Corresponds to orbbec_camera_msgs__srv__GetDeviceInfo
#[allow(missing_docs, non_camel_case_types)]
pub struct GetDeviceInfo;

impl rosidl_runtime_rs::Service for GetDeviceInfo {
    type Request = GetDeviceInfo_Request;
    type Response = GetDeviceInfo_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetDeviceInfo() }
    }
}




#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetCameraInfo() -> *const std::ffi::c_void;
}

// Corresponds to orbbec_camera_msgs__srv__GetCameraInfo
#[allow(missing_docs, non_camel_case_types)]
pub struct GetCameraInfo;

impl rosidl_runtime_rs::Service for GetCameraInfo {
    type Request = GetCameraInfo_Request;
    type Response = GetCameraInfo_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetCameraInfo() }
    }
}




#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetInt32() -> *const std::ffi::c_void;
}

// Corresponds to orbbec_camera_msgs__srv__GetInt32
#[allow(missing_docs, non_camel_case_types)]
pub struct GetInt32;

impl rosidl_runtime_rs::Service for GetInt32 {
    type Request = GetInt32_Request;
    type Response = GetInt32_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetInt32() }
    }
}




#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetString() -> *const std::ffi::c_void;
}

// Corresponds to orbbec_camera_msgs__srv__GetString
#[allow(missing_docs, non_camel_case_types)]
pub struct GetString;

impl rosidl_runtime_rs::Service for GetString {
    type Request = GetString_Request;
    type Response = GetString_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__GetString() }
    }
}




#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__SetInt32() -> *const std::ffi::c_void;
}

// Corresponds to orbbec_camera_msgs__srv__SetInt32
#[allow(missing_docs, non_camel_case_types)]
pub struct SetInt32;

impl rosidl_runtime_rs::Service for SetInt32 {
    type Request = SetInt32_Request;
    type Response = SetInt32_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__SetInt32() }
    }
}




#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__SetString() -> *const std::ffi::c_void;
}

// Corresponds to orbbec_camera_msgs__srv__SetString
#[allow(missing_docs, non_camel_case_types)]
pub struct SetString;

impl rosidl_runtime_rs::Service for SetString {
    type Request = SetString_Request;
    type Response = SetString_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__SetString() }
    }
}




#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__SetStreamProfile() -> *const std::ffi::c_void;
}

// Corresponds to orbbec_camera_msgs__srv__SetStreamProfile
#[allow(missing_docs, non_camel_case_types)]
pub struct SetStreamProfile;

impl rosidl_runtime_rs::Service for SetStreamProfile {
    type Request = SetStreamProfile_Request;
    type Response = SetStreamProfile_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__orbbec_camera_msgs__srv__SetStreamProfile() }
    }
}


