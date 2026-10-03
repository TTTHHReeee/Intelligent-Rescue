# RGB-D 对齐与鼠标点击测距 Demo

## 1. Demo 概述

本章完成了第二个视觉基础 Demo：在彩色图和深度图已经对齐的前提下，点击彩色图中的任意位置，程序读取深度图中对应位置附近的有效深度，并在终端输出距离。

核心数据链路：

~~~text
Gemini Max
    ↓
Orbbec ROS 2 驱动
    ↓
/camera/color/image_raw       /camera/depth/image_raw
              ↓               ↓
        message_filters 近似时间同步
                      ↓
             rgbd_callback()
                      ↓
      彩色图显示 + 鼠标获取像素坐标
                      ↓
       在对齐深度图读取相同像素区域
                      ↓
       过滤0值并计算深度中位数
                      ↓
              输出距离 Z
~~~

核心结论：

> 深度图注册到彩色相机坐标系后，彩色图像素 (u, v) 可以直接对应深度图中的 depth_image[v, u]。

---

## 2. 运行环境

- 平台：Jetson Orin Nano Super 4GB
- 系统：Ubuntu 22.04
- ROS 2：Humble
- 相机：Orbbec Gemini Max
- 工作空间：~/orbbec_ros2_ws
- 功能包：depth_demo
- 节点：rgbd_click_distance
- 彩色话题：/camera/color/image_raw
- 深度话题：/camera/depth/image_raw
- 彩色图：640×480
- 对齐深度图：640×480，编码为 16UC1
- 相机频率：约 30 Hz

终端分工：

~~~text
VS Code Remote-SSH：启动相机、编辑代码、编译功能包
MobaXterm X11 SSH：运行 OpenCV 窗口和鼠标点击程序
~~~

---

## 3. Demo 目标

1. 同时订阅彩色图和深度图。
2. 按时间匹配彩色帧和深度帧。
3. 在 OpenCV 窗口显示彩色图。
4. 获取鼠标点击位置的像素坐标 (u, v)。
5. 读取对齐深度图中相同位置的深度。
6. 截取点击点附近的 11×11 区域。
7. 过滤深度值为 0 的无效像素。
8. 计算有效深度中位数。
9. 输出毫米、米、有效像素数和时间差。

---

## 4. ROS 2 命令及通用格式

ROS 2 命令的一般格式：

~~~bash
ros2 <命令组> <具体命令> [选项]
~~~

### 4.1 加载环境

~~~bash
source /opt/ros/humble/setup.bash
source ~/orbbec_ros2_ws/install/setup.bash
~~~

第一条加载系统 ROS 2，第二条加载工作空间中的功能包。

### 4.2 启动相机

通用格式：

~~~bash
ros2 launch <功能包名> <launch文件> 参数名:=参数值
~~~

本次使用：

~~~bash
ros2 launch orbbec_camera ob_camera.launch.py \
  enable_color:=true \
  enable_depth:=true \
  depth_registration:=true \
  color_format:=MJPG \
  depth_format:=Y12 \
  enable_ir:=false \
  enable_point_cloud:=false
~~~

关键参数：

| 参数 | 作用 |
| --- | --- |
| enable_color:=true | 开启彩色流 |
| enable_depth:=true | 开启深度流 |
| depth_registration:=true | 将深度注册到彩色坐标系 |
| color_format:=MJPG | 使用相机支持的彩色格式 |
| depth_format:=Y12 | 使用 Gemini Max 支持的深度格式 |
| enable_ir:=false | 暂时关闭红外 |
| enable_point_cloud:=false | 暂时关闭点云 |

### 4.3 查看话题

~~~bash
ros2 topic list
ros2 topic type <话题名>
ros2 topic echo <话题名> --once
ros2 topic hz <话题名>
~~~

本次检查：

~~~bash
ros2 topic type /camera/color/image_raw
ros2 topic type /camera/depth/image_raw
ros2 topic hz /camera/color/image_raw
ros2 topic hz /camera/depth/image_raw
~~~

两路频率都约为 30 Hz，消息类型都是：

~~~text
sensor_msgs/msg/Image
~~~

### 4.4 查看节点

~~~bash
ros2 node list
ros2 node info /rgbd_click_distance
~~~

关键订阅关系：

~~~text
Subscribers:
  /camera/color/image_raw: sensor_msgs/msg/Image
  /camera/depth/image_raw: sensor_msgs/msg/Image
~~~

### 4.5 编译与运行

~~~bash
colcon build --packages-select depth_demo --symlink-install
python3 -m py_compile depth_demo/rgbd_click_distance.py
ros2 run depth_demo rgbd_click_distance
~~~

### 4.6 检查 X11

~~~bash
echo $DISPLAY
xdpyinfo | head
~~~

正确结果类似：

~~~text
name of display: localhost:10.0
vendor string: Moba/X
~~~

这证明 MobaXterm 的图形转发正常。

---

## 5. 为什么需要两个节点

~~~text
相机驱动节点：读取硬件并发布彩色图、深度图
点击测距节点：订阅图像并处理像素、深度
~~~

因此：

~~~text
终端一：ros2 launch ...       发布数据
终端二：ros2 run ...          订阅并处理数据
~~~

两个节点可以同时运行在同一台 Jetson 上。

---

## 6. 近似时间同步

程序使用：

~~~python
message_filters.ApproximateTimeSynchronizer(
  [color_subscriber, depth_subscriber],
  queue_size=3,
  slop=0.1,
)
~~~

- queue_size=3：只暂存少量消息，避免使用太旧的图像。
- slop=0.1：允许两条消息时间相差不超过 100 ms。

匹配成功后执行：

~~~python
rgbd_callback(color_msg, depth_msg)
~~~

程序计算两帧时间差：

~~~python
time_difference_ms = abs(color_time - depth_time) * 1000.0
~~~

本次实际时间差约在 1 ms 到 92 ms 之间波动，说明两路消息可以匹配，但时间差会受传感器时间戳、消息队列、Python 处理和 X11 显示影响。

---

## 7. 鼠标点击测距逻辑

### 7.1 获取像素坐标

OpenCV 鼠标回调得到 x、y，在图像处理中对应：

~~~text
u = x
v = y
~~~

由于深度图已经对齐到彩色图，可以读取：

~~~python
depth_image[v, u]
~~~

NumPy 图像索引顺序是 [y, x]，不是 [x, y]。

### 7.2 读取 11×11 区域

以点击点为中心、半径为 5：

~~~text
(5 + 1 + 5) × (5 + 1 + 5) = 121 个像素
~~~

区域统计比单像素更能抵抗噪声和空洞。

### 7.3 过滤无效深度并求中位数

~~~python
valid_depths = region[region > 0]
depth_mm = np.median(valid_depths)
depth_m = depth_mm / 1000.0
~~~

深度值 0 表示没有有效测量，不能当成真实的 0 mm。

---

## 8. 实际运行结果

本次成功输出：

~~~text
Clicked pixel: (u=94, v=220)
valid_pixels: 121
Depth: 956 mm / 0.956 m
Time diff: 17.69 ms
~~~

另一次点击输出：

~~~text
Clicked pixel: (u=566, v=200)
valid_pixels: 121
Depth: 2303 mm / 2.303 m
Time diff: 5.60 ms
~~~

这说明：

1. 鼠标坐标获取成功；
2. 彩色图与深度图像素对应成功；
3. 点击区域的 121 个像素都有效；
4. 点击不同位置可以得到不同距离；
5. 毫米到米的转换正确。

因此，本次 RGB-D 点击测距 Demo 已经完成。

---

## 9. 本次问题及解决方法

### 9.1 VS Code 终端没有图形显示

现象：

~~~text
could not connect to display
Can't initialize GTK backend
~~~

原因：VS Code Remote-SSH 终端没有自动提供 X11。

解决：VS Code 负责代码和相机驱动，MobaXterm 负责 X11 窗口。

### 9.2 DISPLAY 格式错误

错误做法：

~~~bash
export DISPLAY=0
export DISPLAY=1
~~~

这些值不会创建图形服务器。正确值应由 X11 转发自动生成，例如 localhost:10.0。

### 9.3 节点启动但没有窗口

原因：原代码把 cv2.imshow() 放在 if self.clicked_point is not None 内部，必须先点击才能显示窗口，形成逻辑死循环。

解决：把 cv2.imshow() 放到点击判断之外，第一帧到达时就显示窗口。

### 9.4 缺少 cv2.waitKey()

必须调用：

~~~python
key = cv2.waitKey(1) & 0xFF
~~~

它负责窗口刷新、鼠标事件和键盘事件。

### 9.5 key 未定义

原代码直接判断 key，但没有调用 waitKey。补上 waitKey 后解决。

### 9.6 cv2.putText() 收到元组

错误写法：

~~~python
text = (f'{x}, {y}', f'{depth_mm:.0f}mm')
~~~

正确写法：

~~~python
text = (
  f'Pixel=({x}, {y})  '
  f'{depth_mm:.0f} mm'
)
~~~

相邻 f-string 会自动拼接成字符串。

### 9.7 无效深度返回值数量不一致

调用方需要两个值：

~~~python
depth_mm, valid_count = self.get_region_depth(...)
~~~

因此无效时也要返回：

~~~python
return None, 0
~~~

### 9.8 ROS 2 日志函数参数错误

日志函数需要一条完整字符串，不能传多个独立位置参数。应使用多个相邻 f-string 拼接成一条字符串。

### 9.9 Ctrl+C 后出现 rosout 错误

现象：

~~~text
publisher's context is invalid
rcl_shutdown already called
~~~

原因：ROS 上下文可能已经关闭，退出流程又尝试发布日志或再次关闭 ROS。

改进：

~~~python
if rclpy.ok():
  rclpy.shutdown()
~~~

该问题发生在退出阶段，不影响已经完成的测距结果。

### 9.10 远程窗口延迟

原因：MobaXterm 使用 X11 转发显示 OpenCV 窗口，X11 不适合高帧率视频传输。

优化：

~~~python
queue_size=3
slop=0.1
~~~

也可以每 3 帧显示 1 帧，减少 X11 传输压力。

---

## 10. GPU 使用率为 0 的原因

本次 Demo 没有使用 CUDA 或 TensorRT，主要处理都在 CPU 上：

~~~text
rclpy + message_filters + cv_bridge + NumPy + OpenCV GTK + X11
~~~

因此 jtop 中 GPU 为 0% 是正常的。只有主动使用 CUDA OpenCV、TensorRT、PyTorch CUDA、DeepStream 或 NVIDIA GStreamer 硬件加速时，GPU 才会参与主要计算。

当前 Demo 的目标是理解 RGB-D 像素对应关系，不需要 GPU 加速。

---

## 11. Demo 完成标准

- 彩色图正常发布；
- 深度图正常发布；
- 两路频率约 30 Hz；
- 点击节点成功订阅两个图像话题；
- X11 图形转发正常；
- OpenCV 窗口正常显示；
- 可以点击彩色图像素；
- 深度图对应位置返回有效深度；
- 有效区域达到 121 个像素；
- 距离可以以毫米和米输出；
- 点击不同位置得到不同距离。

这说明已经完成了一个可用的 RGB-D 局部测距模块。

---

## 12. 当前 Demo 的局限

当前得到的是深度值 Z，表示物体沿相机光轴方向的距离，还不是完整三维坐标：

~~~text
Z 不等于一般情况下的空间直线距离
~~~

点击物体边缘时，11×11 区域可能同时包含前景和背景，中位数不一定只代表目标。

当前程序还依赖 X11 远程窗口，不适合直接用于低延迟机器人控制。后续可以使用 Jetson 本机显示、Web 界面、ROS 图像压缩或专门的视频传输方式。

---

## 13. 下一步 Demo：YOLO + 深度融合

下一步学习：

~~~text
YOLO检测目标
→ 获取目标检测框
→ 取检测框中心或内部区域
→ 读取对齐深度
→ 得到目标距离
~~~

检测框为 x1、y1、x2、y2 时，中心为：

~~~text
u = (x1 + x2) / 2
v = (y1 + y2) / 2
~~~

后续程序将输出：

~~~text
类别、置信度、检测框、目标深度
~~~

不能只读取检测框中心一个像素，因为中心可能是深度空洞、反光点、遮挡区域或背景。后续会在检测框内部避开边缘，统计有效深度中位数。

下一步新增知识：

- YOLO 推理结果结构；
- 检测框坐标；
- 目标框裁剪；
- 有效深度统计；
- 置信度阈值；
- 类别过滤；
- FPS 和推理延迟；
- Jetson GPU 推理；
- TensorRT 加速。

---

## 14. 后续完整学习路径

### 第 1 阶段：RGB-D 基础

已完成：

1. 深度基础 Demo；
2. 彩色图和深度图对齐验证；
3. 鼠标点击彩色图返回深度。

### 第 2 阶段：YOLO 与深度融合

1. YOLO 检测目标；
2. 从目标框提取有效深度；
3. 输出类别、置信度和距离；
4. 计算目标相机坐标 X、Y、Z。

### 第 3 阶段：相机坐标系与三维坐标

读取相机内参 fx、fy、cx、cy：

~~~text
X = (u - cx) × Z / fx
Y = (v - cy) × Z / fy
Z = 深度值
~~~

### 第 4 阶段：TF 坐标变换

~~~text
camera_color_optical_frame
        ↓ TF外参
camera_link
        ↓ TF外参
base_link
~~~

目标是把相机坐标系中的目标转换到机器人坐标系。

### 第 5 阶段：安全区域局部模型

- 检测物体周围安全区域；
- 检测障碍物边界；
- 拟合桌面、墙面和隔板；
- 输出目标相对于安全区域的位置。

### 第 6 阶段：视觉闭环对准

~~~text
检测目标
→ 计算目标偏差
→ 机器人低速运动
→ 重新检测
→ 误差变小后停止
~~~

### 第 7 阶段：RGB-D SLAM 独立 Demo

先不加载 YOLO，单独运行 RGB-D SLAM，观察漂移、回环、丢失恢复、CPU 和内存占用。

### 第 8 阶段：全局定位对比

对比：

~~~text
编码器 + IMU
RGB-D SLAM
2D激光 + AMCL
~~~

比较漂移、回环、丢失恢复、环境要求、光照敏感性、动态物体影响和资源占用。

---

## 15. 当前学习成果

已经完成从真实传感器到局部三维感知的完整链路：

~~~text
深度相机
→ ROS 2驱动
→ 图像话题
→ 自定义Python节点
→ 彩色/深度对齐
→ 鼠标像素选择
→ 有效深度统计
→ 距离输出
~~~

这已经不只是运行官方节点，而是完成了一个属于自己的 RGB-D 感知程序。下一步将把人工点击替换为 YOLO 自动检测框，再把目标距离扩展为目标三维坐标。
