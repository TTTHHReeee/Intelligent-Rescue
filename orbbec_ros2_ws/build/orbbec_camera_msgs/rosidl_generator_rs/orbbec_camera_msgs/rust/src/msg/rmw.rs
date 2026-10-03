#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__DeviceInfo() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__msg__DeviceInfo__init(msg: *mut DeviceInfo) -> bool;
    fn orbbec_camera_msgs__msg__DeviceInfo__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo>, size: usize) -> bool;
    fn orbbec_camera_msgs__msg__DeviceInfo__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo>);
    fn orbbec_camera_msgs__msg__DeviceInfo__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DeviceInfo>, out_seq: *mut rosidl_runtime_rs::Sequence<DeviceInfo>) -> bool;
}

// Corresponds to orbbec_camera_msgs__msg__DeviceInfo
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DeviceInfo {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub serial_number: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub firmware_version: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub supported_min_sdk_version: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub hardware_version: rosidl_runtime_rs::String,

}



impl Default for DeviceInfo {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__msg__DeviceInfo__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__msg__DeviceInfo__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DeviceInfo {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__DeviceInfo__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__DeviceInfo__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__DeviceInfo__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DeviceInfo {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DeviceInfo where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/msg/DeviceInfo";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__DeviceInfo() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__Extrinsics() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__msg__Extrinsics__init(msg: *mut Extrinsics) -> bool;
    fn orbbec_camera_msgs__msg__Extrinsics__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Extrinsics>, size: usize) -> bool;
    fn orbbec_camera_msgs__msg__Extrinsics__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Extrinsics>);
    fn orbbec_camera_msgs__msg__Extrinsics__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Extrinsics>, out_seq: *mut rosidl_runtime_rs::Sequence<Extrinsics>) -> bool;
}

// Corresponds to orbbec_camera_msgs__msg__Extrinsics
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Extrinsics {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rotation: [f64; 9],


    // This member is not documented.
    #[allow(missing_docs)]
    pub translation: [f64; 3],

}



impl Default for Extrinsics {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__msg__Extrinsics__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__msg__Extrinsics__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Extrinsics {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__Extrinsics__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__Extrinsics__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__Extrinsics__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Extrinsics {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Extrinsics where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/msg/Extrinsics";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__Extrinsics() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__Metadata() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__msg__Metadata__init(msg: *mut Metadata) -> bool;
    fn orbbec_camera_msgs__msg__Metadata__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Metadata>, size: usize) -> bool;
    fn orbbec_camera_msgs__msg__Metadata__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Metadata>);
    fn orbbec_camera_msgs__msg__Metadata__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Metadata>, out_seq: *mut rosidl_runtime_rs::Sequence<Metadata>) -> bool;
}

// Corresponds to orbbec_camera_msgs__msg__Metadata
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Metadata {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub json_data: rosidl_runtime_rs::String,

}



impl Default for Metadata {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__msg__Metadata__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__msg__Metadata__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Metadata {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__Metadata__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__Metadata__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__Metadata__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Metadata {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Metadata where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/msg/Metadata";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__Metadata() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__IMUInfo() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__msg__IMUInfo__init(msg: *mut IMUInfo) -> bool;
    fn orbbec_camera_msgs__msg__IMUInfo__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<IMUInfo>, size: usize) -> bool;
    fn orbbec_camera_msgs__msg__IMUInfo__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<IMUInfo>);
    fn orbbec_camera_msgs__msg__IMUInfo__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<IMUInfo>, out_seq: *mut rosidl_runtime_rs::Sequence<IMUInfo>) -> bool;
}

// Corresponds to orbbec_camera_msgs__msg__IMUInfo
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct IMUInfo {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub noise_density: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub random_walk: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reference_temperature: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bias: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub gravity: [f64; 3],


    // This member is not documented.
    #[allow(missing_docs)]
    pub scale_misalignment: [f64; 9],


    // This member is not documented.
    #[allow(missing_docs)]
    pub temperature_slope: [f64; 9],

}



impl Default for IMUInfo {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__msg__IMUInfo__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__msg__IMUInfo__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for IMUInfo {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__IMUInfo__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__IMUInfo__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__IMUInfo__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for IMUInfo {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for IMUInfo where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/msg/IMUInfo";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__IMUInfo() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__RGBD() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__msg__RGBD__init(msg: *mut RGBD) -> bool;
    fn orbbec_camera_msgs__msg__RGBD__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RGBD>, size: usize) -> bool;
    fn orbbec_camera_msgs__msg__RGBD__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RGBD>);
    fn orbbec_camera_msgs__msg__RGBD__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RGBD>, out_seq: *mut rosidl_runtime_rs::Sequence<RGBD>) -> bool;
}

// Corresponds to orbbec_camera_msgs__msg__RGBD
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// RGBD Message

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RGBD {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rgb_camera_info: sensor_msgs::msg::rmw::CameraInfo,


    // This member is not documented.
    #[allow(missing_docs)]
    pub depth_camera_info: sensor_msgs::msg::rmw::CameraInfo,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rgb: sensor_msgs::msg::rmw::Image,


    // This member is not documented.
    #[allow(missing_docs)]
    pub depth: sensor_msgs::msg::rmw::Image,

}



impl Default for RGBD {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__msg__RGBD__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__msg__RGBD__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RGBD {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__RGBD__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__RGBD__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__RGBD__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RGBD {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RGBD where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/msg/RGBD";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__RGBD() }
  }
}


#[link(name = "orbbec_camera_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__StreamProfile() -> *const std::ffi::c_void;
}

#[link(name = "orbbec_camera_msgs__rosidl_generator_c")]
extern "C" {
    fn orbbec_camera_msgs__msg__StreamProfile__init(msg: *mut StreamProfile) -> bool;
    fn orbbec_camera_msgs__msg__StreamProfile__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<StreamProfile>, size: usize) -> bool;
    fn orbbec_camera_msgs__msg__StreamProfile__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<StreamProfile>);
    fn orbbec_camera_msgs__msg__StreamProfile__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<StreamProfile>, out_seq: *mut rosidl_runtime_rs::Sequence<StreamProfile>) -> bool;
}

// Corresponds to orbbec_camera_msgs__msg__StreamProfile
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StreamProfile {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stream_name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub width: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub height: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fps: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub format: rosidl_runtime_rs::String,

}



impl Default for StreamProfile {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !orbbec_camera_msgs__msg__StreamProfile__init(&mut msg as *mut _) {
        panic!("Call to orbbec_camera_msgs__msg__StreamProfile__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for StreamProfile {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__StreamProfile__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__StreamProfile__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { orbbec_camera_msgs__msg__StreamProfile__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for StreamProfile {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for StreamProfile where Self: Sized {
  const TYPE_NAME: &'static str = "orbbec_camera_msgs/msg/StreamProfile";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__orbbec_camera_msgs__msg__StreamProfile() }
  }
}


