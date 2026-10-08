# 工训视觉工程导览

>  工程包含两条视觉实验线和一套小车控制固件，**不要把整个文件夹当作一个可以直接运行的 Python 项目**。以下结论基于当前文件结构和源码；资料 PDF 、比赛规则、硬件规格仍以原文件为准。

> **本项目已建立git仓库，可使用git log查看历史提交状态**，但不是必须使用，**仅供参考**

> 项目架构等均按照个人习惯，**可随意更改或重新创建**

**往届主代码参考位置**

~~~~
控制代码：工训\2025年4月13日-白车
视觉代码：① 工训\maixpy\code\MAIN.py
         ② 工训\maixpy\code\original_main_1.py
         ③ 工训\maixpy\code\original_main_2.py

~~~~

## 项目架构

```text
MaixCAM2 视觉线
相机采图 -> 标注/划分数据集 -> YOLO26 训练 -> ONNX 导出
         -> MaixHub 转 MUD/axmodel -> MaixCAM2 识别程序 推理/选目标/判断抓取/阶段切换 -> UART 目标坐标
                                                              							|
                                                        							  控制端

Jetson RGB-D 实验线（目前独立）
Gemini Max -> Orbbec ROS 2 驱动 -> RGB/深度话题 -> YOLO + 深度 Demo
```

MaixCAM2 和 Jetson 的脚本运行在**不同设备/环境**

## 主要目录地图

### 根目录

| 位置                               | 用途                                  | 备注                                                         |
| ---------------------------------- | ------------------------------------- | ------------------------------------------------------------ |
| `.\2025年4月13日-白车`             | 往届小车控制端代码                    | 可参考拓展学习                                               |
| `.\best`                           | 基于x-anylabeling的自定义模型部署工具 | 每训练好一次模型，可将onnx模型进行覆盖替换，用于下一次的半自动化标注 |
| `.\datasets`                       | 汇总每一轮新添加的数据集              | 数据集备份                                                   |
| `.\datasets_1`                     | 第一轮采集的数据集                    | \                                                            |
| `.\datasets_2`                     | 第二轮采集的数据集                    | \                                                            |
| `.\test_datasets_1`                | 第一轮用于训练自定义模型              | 先手动标注30~50份数据，训练好模型后基于x-anylabeling使用该模型对剩下的数据进行ai自动化标注 |
| `.\test_datasets_2`                | 第二轮用于训练自定义模型              | 同上                                                         |
| `.\maixpy`                         | 代码、maixcam支持模型的存放位置       | \                                                            |
| `.\深度流测试学习代码`             | 基于ros的深度流学习代码               | 供参考，可忽略                                               |
| `.\maixpy-skill.zip`               | sipeed官方提供AI资源                  | 可搭建本地maixcam ai开发流，帮助开发                         |
| `.\X-AnyLabeling-main.zip`         | x-anylabeling资源，可直接部署在本地   | 可自行检查github上有无最新版本                               |
| `.\工训规则.pdf`                   | 智能救援官方规则                      | \                                                            |
| `.\屏幕录制 2026-10-03 051923.mp4` | \                                     | 供参考，可忽略                                               |

### `maixpy`目录

| 位置 | 用途 | 备注 |
| --- | --- | --- |
| `./code` | MaixCAM2 推理、UART、数据处理及训练/导出脚本 | 核心视觉线 |
| `./code/runs` | 模型训练导出位置 | 训练时自动生成 |
| `./code/weights` | 初始模型存放位置 | \ |
| `./model` | MaixHub 导出的不同批次 MUD、NPU/VNPU 模型及 ZIP | 部署产物 |

`orbbec_ros2_ws/src/OrbbecSDK_ROS2` 在 Git 中是独立的 gitlink（子仓库），其上游驱动、`build/`、`install/` 和 `Log/` 不应和本项目自写业务代码混为一谈。根目录的 `maixpy-skill.zip` 与 `maixpy/` 下的 skill 文件是开发辅助工具，并非设备运行脚本。


## `maixpy/code` 文件用途与备注

下面按当前项目中的脚本和截图中列出的文件说明其职责。路径中的 `./code` 指 `maixpy/code`。

| 位置 | 用途 | 备注 |
| --- | --- | --- |
| `./code` | MaixCAM2 推理、UART、数据处理以及训练/导出脚本 | 核心视觉线；设备端脚本与 PC 端训练脚本共存，运行前先确认脚本目标环境。 |
| `./code/comm_uart.py` | 配置 MaixCAM2 的 UART4，并进行串口数据发送、接收和回环测试 | 默认使用 A21/A22 与 `/dev/ttyS4`；串口助手和设备端必须统一波特率、接线、帧格式及字节序。 |
| `./code/diagnose_model_outputs.py` | 检查 ONNX/MUD 模型的输入输出数量、名称、形状和元数据 | 用于诊断模型输出格式；不是正式推理入口，适合排查 `nn.YOLO26()` 无法解析模型的问题。 |
| `./code/export_maix_yolo26_raw.py` | 导出包含 YOLO26 原始六路检测输出的 ONNX 模型 | 三路 `one2one_cv2` 为边框回归输出，三路 `one2one_cv3` 为分类输出；输入模型、节点名称和输出文件路径要与当前模型匹配。 |
| `./code/frame.py` | 从 MaixCAM2 摄像头采集画面并按帧抽取图片 | 默认每 30 帧保存一张到设备端 `/root/images_2`；保存位置属于设备文件系统，不是 Windows 项目目录。 |
| `./code/MAIN.py` | MaixCAM2 主视觉程序：加载模型、摄像头推理、目标筛选、画面显示并通过 UART 发送坐标 | 核心设备端入口；需要与部署的 MUD 模型、类别顺序和 STM32 串口协议保持一致。当前源码中的阶段/区域判断、空目标处理和目标锁定等逻辑仍需按实际任务复核。 |
| `./code/original_main_1.py`        | 往届代码                                                     | \ |
| `./code/original_main_2.py` | 往届代码 | \ |
| `./code/pinmap_demo.py` | 验证 MaixCAM2 引脚复用配置和 UART 引脚映射 | 用于确认 A21/A22 与 UART4 的对应关系，不等于完整的串口业务程序；修改引脚前要确认硬件接线。 |
| `./code/quantize_int8.py` | 使用 ONNX Runtime 校准图片进行 ONNX 静态 INT8 量化 | 该文件可直接忽略，该文件为测试文件，生成量化 ONNX 后要重新验证精度、输入输出格式和 MaixHub/MaixCAM2 转换兼容性；不能直接把它当作 MUD 转换脚本。 |
| `./code/rename_files.py` | 按自然顺序为数据集图片和标注文件重新编号/重命名 | 图片和标签必须同步处理；运行前核对全局路径、配对关系及是否允许覆盖，必要时先**备份**。 |
| `./code/restore_txt_to_json.py` | 根据 YOLO TXT 标注和图片恢复对应的 LabelMe JSON 文件 | 需要正确的类别映射和图片文件名；输入压缩包的目录结构必须符合脚本预期，否则会出现找不到 `classes.txt` 或图片的错误。 |
| `./code/split_dataset.py` | 按设定比例划分数据集的训练集和验证集，并同步处理图片与标签 | 可修改比例（如 7:3、8:2）、源/目标路径以及复制或移动策略；运行前核对 `DRY_RUN`、覆盖策略和缺失标签处理设置。 |
| `./code/train.py` | 使用 Ultralytics 训练 YOLO 模型并导出 ONNX | 当前主程序调用的是导出流程；模型路径、`data.yaml` 和输出目录是本机路径，**换电脑或换数据集时需要修改**，并确认 PyTorch CUDA 环境。 |

## MaixCAM2 视觉线

1. **采集**：`maixpy/code/frame.py` 保存到设备 `/root/images`,  `/root/images`或`/root/images_2`都是设备路径，保存的皆是数据集，不是 Windows 工程目录。

2. **数据准备**：[`rename_files.py`](maixpy/code/rename_files.py) 用于给数据集中每个数据进行重编号；[`restore_txt_to_json.py`](maixpy/code/restore_txt_to_json.py) 从 YOLO TXT 恢复标注 JSON，防止在处理数据集中误操作丢失源标注文件；[`split_dataset.py`](maixpy/code/split_dataset.py) 按全局比例复制/移动图像和标签到 `train/val`。运行这些会改动文件，先核对脚本顶部路径、`DRY_RUN`、`MOVE_FILES` 等设置。

3. **训练**：数据集中的 `data.yaml` 决定 `train`、`val` 和类别顺序。[`train.py`](maixpy/code/train.py) 使用 Ultralytics；当前文件的主入口调用 `export_yolo_model()`，训练函数并未在主入口执行。训练实验和权重在 [`maixpy/code/runs/detect/`](maixpy/code/runs/detect/) 的 `train`、`train-2` ... `train-6` 下；`args.yaml` 保存当次参数。

4. **导出/转换**：训练权重 `best.pt` 导出 `best.onnx`；[`export_maix_yolo26_raw.py`](maixpy/code/export_maix_yolo26_raw.py) 将 YOLO26 的三路 bbox 和三路分类头暴露为六路 ONNX 输出，生成 `best_maix.onnx`，然后供网页转换流程使用。[`diagnose_model_outputs.py`](maixpy/code/diagnose_model_outputs.py) 用于检查输出；[`quantize_int8.py`](maixpy/code/quantize_int8.py) 是另一个 ONNX 量化实验，不能把其产物自动视为 MaixCAM2 部署模型。转换生成的 MUD 引用同包里的 `*_npu.axmodel` 和 `*_vnpu.axmodel`。

5. **设备推理**：[`MAIN.py`](maixpy/code/MAIN.py) 当前指向设备 `/root/my_model/model_9540.mud`，用 `nn.NN` 读取六路原始输出，手工还原框/类别，随后按阶段选择目标并通过 `/dev/ttyS4` 发送坐标。实际设备运行需 MaixPy 环境与对应模型文件；不要在普通 PC Python 环境直接运行此脚本。UART 独立测试见 [`comm_uart.py`](maixpy/code/comm_uart.py)。

   > 以上为一般做法，如有其它更好的解决方法，可直接忽略

目前 `datasets_2` 和 `test_datasets_2` 的 `data.yaml` 均列出六类：`orange, green, blue, black, zone1, zone2`。旧数据集配置可能只有四类；训练、转换和设备侧标签顺序必须一致。数据集配置里有本机绝对路径，**换电脑时先改路径**。

## 学习资源参考

### sipeed官方网站

> [Sipeed 资料站 - Sipeed Wiki](https://wiki.sipeed.com/)

### maixcam API

> [快速开始 - MaixPy](https://wiki.sipeed.com/maixpy/doc/zh/index.html)

#### 常用API

1. [maix.image - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/image.html)
2. [maix.camera - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/camera.html)
3. [maix.display - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/display.html)
4. [maix.nn - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/nn.html)
5. [maix.app - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/app.html)
6. [maix.time - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/time.html)
7. [maix.peripheral.uart - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/peripheral/uart.html)
8. [maix.app - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/app.html)
9. [maix.peripheral.pinmap - MaixPy](https://wiki.sipeed.com/maixpy/api/maix/peripheral/pinmap.html)
10. [PINMAP IO 功能映射 - MaixPy](https://wiki.sipeed.com/maixpy/doc/zh/peripheral/pinmap.html#API-文档)
11. [UART 串口 - MaixPy](https://wiki.sipeed.com/maixpy/doc/zh/peripheral/uart.html)
12. [手动转换给 MaixCAM2 用 - MaixPy](https://wiki.sipeed.com/maixpy/doc/zh/ai_model_converter/maixcam2.html)
13. **[应用开机自启 - MaixPy](https://wiki.sipeed.com/maixpy/doc/zh/basic/auto_start.html)**
14. [MaixHub](https://maixhub.com/app/upload)

### maixhub平台

> [MaixHub](https://maixhub.com/)

### maixcam支持的模型—转换平台

> [MaixHub](https://maixhub.com/toolbox/convert/maixcam)

### netron - 模型可视化工具

> [Netron](https://netron.app/)

### mud模型本地转换

> https://www.bilibili.com/video/BV1h1oLY2EoE/?spm_id_from=333.1387.collection.video_card.click

### x-anylabeling

> [CVHub520/X-AnyLabeling: X-AnyLabeling: A lightweight, efficient, and unified cross-platform desktop application for annotating text, image, video, and multimodal data, combining versatile built-in tools with state-of-the-art AI models and flexible multi-format export.](https://github.com/CVHub520/X-AnyLabeling)

### Gemini 深度相机

> Gemini Max深度相机   https://www.yahboom.com/study/Gemini-Max   提取码：gmax

### jetson orin nano super (运存4G)

> Jetson Orin NANO SUPER官网资料：   https://www.yahboom.com/study/Orin-Nano-SUPER     密码：lguu



## Gemini / Jetson RGB-D 实验线

> **该线可用于自身学习、能力提升，比赛暂不需要，如有想法，可大胆与老师，队友分享**

> **jetson上已部署gemini max的python和ros的相关驱动**。

[`depth_viewer.py`](depth_viewer.py) 使用 Orbbec Python SDK 独立读取和显示深度帧；[`yolo_depth_demo.py`](yolo_depth_demo.py) 是 ROS 2 节点，订阅 `/camera/color/image_raw` 和 `/camera/depth/image_raw`，使用 Ultralytics 检测框，从同尺寸、时间差不超过阈值的深度图中计算有效深度中位数。它默认从 Jetson 的 `/home/jetson/orbbec_ros2_ws/models/yolo26n.pt` 读取权重，并非引用当前 Windows 目录里的模型。

驱动源码在 [`orbbec_ros2_ws/src/OrbbecSDK_ROS2/`](orbbec_ros2_ws/src/OrbbecSDK_ROS2/)；当前仓库里未发现总结文档提到的 `depth_demo` 或点击测距节点的独立源码，相关实现/运行步骤主要保留在 [`基础深度Demo总结1.md`](基础深度Demo总结1.md)、[`RGB-D点击测距Demo总结2.md`](RGB-D点击测距Demo总结2.md) 和 [`gemini初次使用总结.md`](gemini初次使用总结.md) 中。ROS 2 部分按文档使用 Jetson/Ubuntu 22.04 + ROS 2 Humble；不要在 Windows PowerShell 中直接运行 ROS 2 工作空间。

