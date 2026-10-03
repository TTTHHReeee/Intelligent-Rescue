#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to orbbec_camera_msgs__msg__DeviceInfo

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DeviceInfo {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub serial_number: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub firmware_version: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub supported_min_sdk_version: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub hardware_version: std::string::String,

}



impl Default for DeviceInfo {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DeviceInfo::default())
  }
}

impl rosidl_runtime_rs::Message for DeviceInfo {
  type RmwMsg = super::msg::rmw::DeviceInfo;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        name: msg.name.as_str().into(),
        serial_number: msg.serial_number.as_str().into(),
        firmware_version: msg.firmware_version.as_str().into(),
        supported_min_sdk_version: msg.supported_min_sdk_version.as_str().into(),
        hardware_version: msg.hardware_version.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        name: msg.name.as_str().into(),
        serial_number: msg.serial_number.as_str().into(),
        firmware_version: msg.firmware_version.as_str().into(),
        supported_min_sdk_version: msg.supported_min_sdk_version.as_str().into(),
        hardware_version: msg.hardware_version.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      name: msg.name.to_string(),
      serial_number: msg.serial_number.to_string(),
      firmware_version: msg.firmware_version.to_string(),
      supported_min_sdk_version: msg.supported_min_sdk_version.to_string(),
      hardware_version: msg.hardware_version.to_string(),
    }
  }
}


// Corresponds to orbbec_camera_msgs__msg__Extrinsics

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Extrinsics {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rotation: [f64; 9],


    // This member is not documented.
    #[allow(missing_docs)]
    pub translation: [f64; 3],

}



impl Default for Extrinsics {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Extrinsics::default())
  }
}

impl rosidl_runtime_rs::Message for Extrinsics {
  type RmwMsg = super::msg::rmw::Extrinsics;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        rotation: msg.rotation,
        translation: msg.translation,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        rotation: msg.rotation,
        translation: msg.translation,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      rotation: msg.rotation,
      translation: msg.translation,
    }
  }
}


// Corresponds to orbbec_camera_msgs__msg__Metadata

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Metadata {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub json_data: std::string::String,

}



impl Default for Metadata {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Metadata::default())
  }
}

impl rosidl_runtime_rs::Message for Metadata {
  type RmwMsg = super::msg::rmw::Metadata;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        json_data: msg.json_data.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        json_data: msg.json_data.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      json_data: msg.json_data.to_string(),
    }
  }
}


// Corresponds to orbbec_camera_msgs__msg__IMUInfo

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct IMUInfo {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::IMUInfo::default())
  }
}

impl rosidl_runtime_rs::Message for IMUInfo {
  type RmwMsg = super::msg::rmw::IMUInfo;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        noise_density: msg.noise_density,
        random_walk: msg.random_walk,
        reference_temperature: msg.reference_temperature,
        bias: msg.bias,
        gravity: msg.gravity,
        scale_misalignment: msg.scale_misalignment,
        temperature_slope: msg.temperature_slope,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      noise_density: msg.noise_density,
      random_walk: msg.random_walk,
      reference_temperature: msg.reference_temperature,
        bias: msg.bias,
        gravity: msg.gravity,
        scale_misalignment: msg.scale_misalignment,
        temperature_slope: msg.temperature_slope,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      noise_density: msg.noise_density,
      random_walk: msg.random_walk,
      reference_temperature: msg.reference_temperature,
      bias: msg.bias,
      gravity: msg.gravity,
      scale_misalignment: msg.scale_misalignment,
      temperature_slope: msg.temperature_slope,
    }
  }
}


// Corresponds to orbbec_camera_msgs__msg__RGBD
/// RGBD Message

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RGBD {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rgb_camera_info: sensor_msgs::msg::CameraInfo,


    // This member is not documented.
    #[allow(missing_docs)]
    pub depth_camera_info: sensor_msgs::msg::CameraInfo,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rgb: sensor_msgs::msg::Image,


    // This member is not documented.
    #[allow(missing_docs)]
    pub depth: sensor_msgs::msg::Image,

}



impl Default for RGBD {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::RGBD::default())
  }
}

impl rosidl_runtime_rs::Message for RGBD {
  type RmwMsg = super::msg::rmw::RGBD;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        rgb_camera_info: sensor_msgs::msg::CameraInfo::into_rmw_message(std::borrow::Cow::Owned(msg.rgb_camera_info)).into_owned(),
        depth_camera_info: sensor_msgs::msg::CameraInfo::into_rmw_message(std::borrow::Cow::Owned(msg.depth_camera_info)).into_owned(),
        rgb: sensor_msgs::msg::Image::into_rmw_message(std::borrow::Cow::Owned(msg.rgb)).into_owned(),
        depth: sensor_msgs::msg::Image::into_rmw_message(std::borrow::Cow::Owned(msg.depth)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        rgb_camera_info: sensor_msgs::msg::CameraInfo::into_rmw_message(std::borrow::Cow::Borrowed(&msg.rgb_camera_info)).into_owned(),
        depth_camera_info: sensor_msgs::msg::CameraInfo::into_rmw_message(std::borrow::Cow::Borrowed(&msg.depth_camera_info)).into_owned(),
        rgb: sensor_msgs::msg::Image::into_rmw_message(std::borrow::Cow::Borrowed(&msg.rgb)).into_owned(),
        depth: sensor_msgs::msg::Image::into_rmw_message(std::borrow::Cow::Borrowed(&msg.depth)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      rgb_camera_info: sensor_msgs::msg::CameraInfo::from_rmw_message(msg.rgb_camera_info),
      depth_camera_info: sensor_msgs::msg::CameraInfo::from_rmw_message(msg.depth_camera_info),
      rgb: sensor_msgs::msg::Image::from_rmw_message(msg.rgb),
      depth: sensor_msgs::msg::Image::from_rmw_message(msg.depth),
    }
  }
}


// Corresponds to orbbec_camera_msgs__msg__StreamProfile

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StreamProfile {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stream_name: std::string::String,


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
    pub format: std::string::String,

}



impl Default for StreamProfile {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::StreamProfile::default())
  }
}

impl rosidl_runtime_rs::Message for StreamProfile {
  type RmwMsg = super::msg::rmw::StreamProfile;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stream_name: msg.stream_name.as_str().into(),
        width: msg.width,
        height: msg.height,
        fps: msg.fps,
        format: msg.format.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stream_name: msg.stream_name.as_str().into(),
      width: msg.width,
      height: msg.height,
      fps: msg.fps,
        format: msg.format.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      stream_name: msg.stream_name.to_string(),
      width: msg.width,
      height: msg.height,
      fps: msg.fps,
      format: msg.format.to_string(),
    }
  }
}


