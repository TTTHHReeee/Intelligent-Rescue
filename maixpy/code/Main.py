"""MaixCAM2 摄像头检测演示：读取 YOLO26 的六路输出并绘制检测结果。"""

import math

import numpy as np

from maix import app, camera, display, image, nn, tensor, time, uart
import struct

# ==================== User-adjustable settings ====================
device = "/dev/ttyS4"
serial = uart.UART(device, 115200)
# 设备上的 MUD 描述文件；同目录下的 axmodel 由 MUD 引用加载。
MODEL_PATH = "/root/my_model/model_9540.mud"
# 某些模型（例如四类别时）的 bbox/class 输出通道数相同，原生 YOLO26
# 解析器可能无法区分它们；True 表示用 nn.NN 读取原始输出并手动解码。
USE_GENERIC_NN = True
# 摄像头尺寸应与模型输入一致，避免缩放或补边影响网格坐标还原。
CAMERA_WIDTH = 640
CAMERA_HEIGHT = 640
# 检测分数下限；越高误检通常越少，但可能漏检。
CONFIDENCE_THRESHOLD = 0.50
# 仅传给原生 nn.YOLO26.detect()；手动解码 one-to-one 输出不使用此参数。
IOU_THRESHOLD = 0.45
# True 时额外打印类别名及分数。
PRINT_DETECTIONS = False

# 检测框和标签的显示样式。
BOX_COLOR = image.COLOR_RED
TEXT_COLOR = image.COLOR_GREEN
TEXT_SCALE = 1.0
BOX_THICKNESS = 1

# 应与 MUD 的 mean/scale 元数据一致；此配置把 0~255 像素归一化到 0~1。
MODEL_MEAN = [0.0, 0.0, 0.0]
MODEL_SCALE = [1.0 / 255.0, 1.0 / 255.0, 1.0 / 255.0]

#类ID映射表
CLASS_ID={
    0 : "orange", # 15
    1 : "green", #  5
    2 : "blue", # 0
    3 : "black", # 10
    4 : "zone1", # 红色安全区
    5 : "zone2", # 蓝色安全区
}
ZONE = 4 # 默认为红色安全区

#阶段配置表 罗列了各个阶段的检测目标（targit_ID），抓取目标的优先级（priority_ID），以及判断是否需要过滤已在安全区中的目标（priority_ID）
Phase_config = {
    "PH0":{
            "target_ID" : [ZONE], # 目标：安全区
            "filter_frames" : False,
            "priority_ID":{ZONE: 0},
    },
    "PH1":{
            "target_ID" : [1], # 目标：5 | 优先级->距离 | 执行2次 | -(抓1个)->PH0->PH1-(抓1个)->PH0->PH2 
            "filter_frames" : True,
            "priority_ID": {1: 0},
    },
    "PH2":{
            "target_ID" : [0, 1, 3], # 目标：5，10， 15 | 优先级->距离 | 执行1次 | -(get_score>=15)->PH0->PH3
            "filter_frames" : True,
            "priority_ID" : {0: 0, 3: 1, 1: 2},
    },


} 





flag = 1 # 阶段转换标志
number = 0 # 记录从执行抓取到安全区一整个流程的次数


Y = 0 # 初始化y 用于临时保存当下y坐标
Y_thres = 400 # y坐标阈值 用于判断目标是否达到已被抓取的标准


# ================================================================


def get_result_value(result, name, default=None):
    """兼容手动解码的字典结果与 nn.YOLO26 返回的对象结果。"""
    if isinstance(result, dict):
        return result.get(name, default)
    return getattr(result, name, default)




def model_labels(model):
    """兼容不同 MaixPy 版本，从 MUD 元数据读取类别名。"""
    # 优先调用封装好的标签接口；旧版本没有该接口时再解析逗号分隔的 labels。
    try:
        labels = model.extra_info_labels()
        if labels:
            return [str(label) for label in labels]
    except Exception:
        pass

    try:
        raw_labels = model.extra_info().get("labels", "")
        labels = [item.strip() for item in raw_labels.split(",") if item.strip()]
        if labels:
            return labels
    except Exception:
        pass

    return []


def generic_output_groups(model):
    """从六路输出中找出三个尺度各自的边框头和分类头。"""
    bbox = []
    cls = []

    # 每个尺度有一张 bbox 网格和一张分类网格，共三对、六个张量。
    # 这里按节点名称识别类型，不靠通道数猜测：四类别时两者通道数都为 4。
    for info in model.outputs_info():
        name = str(info.name)
        shape = list(info.shape)
        if len(shape) != 4:
            continue
        lower_name = name.lower()
        # cv2 是边框距离 (左/上/右/下)，cv3 是分类 logit；名字来自 ONNX 输出节点。
        if "one2one_cv2" in lower_name:
            bbox.append(info)
        elif "one2one_cv3" in lower_name:
            cls.append(info)

    # 640x640 输入通常产生 80x80、40x40、20x20 三层网格；按面积排序配对。
    key = lambda info: int(info.shape[1]) * int(info.shape[2])
    bbox.sort(key=key, reverse=True)
    cls.sort(key=key, reverse=True)

    if len(bbox) != 3 or len(cls) != 3:
        raise RuntimeError(
            "Expected 3 bbox and 3 cls heads, got {} bbox and {} cls".format(
                len(bbox), len(cls)
            )
        )

    # 本模型输出采用 NHWC：[批次, 网格高, 网格宽, 通道数]。
    # bbox 的最后一维固定为 4；cls 的最后一维等于模型类别数。
    for bbox_info, cls_info in zip(bbox, cls):
        if list(bbox_info.shape[:3]) != list(cls_info.shape[:3]):
            raise RuntimeError("bbox and cls grid sizes do not match")
        if bbox_info.shape[0] != 1 or bbox_info.shape[3] != 4:
            raise RuntimeError("Expected NHWC bbox output with batch=1, channels=4")
        if cls_info.shape[3] != cls[0].shape[3] or cls_info.shape[3] <= 0:
            raise RuntimeError("Inconsistent class channel counts")
        if bbox_info.shape[1] <= 0 or bbox_info.shape[2] <= 0:
            raise RuntimeError("Invalid output grid size")
    if len({tuple(info.shape[1:3]) for info in bbox}) != 3:
        raise RuntimeError("Expected three distinct output grid sizes")

    return bbox, cls


def sigmoid(value):
    """将分类 logit 转为 0~1 分数，并避免指数运算溢出。"""
    value = float(value)
    if value >= 0.0:
        exp_value = math.exp(-value)
        return 1.0 / (1.0 + exp_value)
    exp_value = math.exp(value)
    return exp_value / (1.0 + exp_value)


def generic_yolo26_detect(model, frame, bbox_infos, cls_infos):
    """推理六路原始输出，逐尺度还原为检测框、类别和分数。"""
    if frame.width() != CAMERA_WIDTH or frame.height() != CAMERA_HEIGHT:
        raise RuntimeError("Camera frame size differs from the configured model input")
    # forward_image 负责图像预处理和 NPU 推理。输入尺寸相同，因此 FIT_CONTAIN
    # 不会产生额外留白；copy_result 保留本帧输出，dual_buff_wait 等待推理完成。
    outputs = model.forward_image(
        frame,
        mean=MODEL_MEAN,
        scale=MODEL_SCALE,
        fit=image.Fit.FIT_CONTAIN,
        copy_result=True,
        dual_buff_wait=True,
    )
    if outputs is None:
        return []

    results = []
    # 分类输出是 logit，先把概率阈值反算为 logit，筛选后再调用 sigmoid。
    logit_threshold = math.log(CONFIDENCE_THRESHOLD / (1.0 - CONFIDENCE_THRESHOLD))
    for bbox_info, cls_info in zip(bbox_infos, cls_infos):
        # 按输出层名称取张量，转成 NumPy 浮点数组；[0] 去掉 batch=1 这一维。
        # 例如 bbox 为 [80, 80, 4]，cls 为 [80, 80, 类别数]。
        bbox_array = tensor.tensor_to_numpy_float32(
            outputs[bbox_info.name], copy=False
        )[0]
        cls_array = tensor.tensor_to_numpy_float32(
            outputs[cls_info.name], copy=False
        )[0]

        grid_height = int(bbox_info.shape[1])
        grid_width = int(bbox_info.shape[2])
        # 网格来自模型检测头的下采样特征图，并非先检测到目标后才生成。
        # 640 输入下，80/40/20 网格的每格分别对应原图 8/16/32 像素。
        stride_x = float(CAMERA_WIDTH) / grid_width
        stride_y = float(CAMERA_HEIGHT) / grid_height
        if tuple(bbox_array.shape) != tuple(bbox_info.shape[1:]):
            raise RuntimeError("Unexpected bbox tensor layout")
        if tuple(cls_array.shape) != tuple(cls_info.shape[1:]):
            raise RuntimeError("Unexpected class tensor layout")

        # 每个网格位置都是一个候选预测，不一定有目标；先取其最高分类分数。
        # np.nonzero 返回过阈值位置的 (行, 列)，即后面的 (grid_y, grid_x)。
        class_ids = np.argmax(cls_array, axis=-1)
        logits = np.max(cls_array, axis=-1)
        rows, cols = np.nonzero(np.isfinite(logits) & (logits >= logit_threshold))
        for grid_y, grid_x in zip(rows, cols):
            distances = bbox_array[grid_y, grid_x]
            if not np.all(np.isfinite(distances)):
                continue
            left, top, right, bottom = (float(v) for v in distances)
            # cv2 的四个距离以网格步长为单位；相对网格中心换算成原图角点。
            center_x = (int(grid_x) + 0.5) * stride_x
            center_y = (int(grid_y) + 0.5) * stride_y
            # 两个角点分别裁到图像范围内，避免得到超出屏幕的框宽高。
            x1 = max(0.0, min(center_x - left * stride_x, float(CAMERA_WIDTH)))
            y1 = max(0.0, min(center_y - top * stride_y, float(CAMERA_HEIGHT)))
            x2 = max(0.0, min(center_x + right * stride_x, float(CAMERA_WIDTH)))
            y2 = max(0.0, min(center_y + bottom * stride_y, float(CAMERA_HEIGHT)))
            if x2 - x1 < 1.0 or y2 - y1 < 1.0:
                continue
            results.append(
                {
                    "x": x1,
                    "y": y1,
                    "w": x2 - x1,
                    "h": y2 - y1,
                    "class_id": int(class_ids[grid_y, grid_x]),
                    "score": sigmoid(logits[grid_y, grid_x]),
                }
            )

    # 每个有效候选变成一个检测字典；one-to-one 输出在此不做 NMS。
    # x/y 是左上角，w/h 是尺寸，class_id 是类别下标，score 是 sigmoid 后的分数。
    return results

"""
此方法功能：反映抓取过程 判断抓取到的目标是否符合要求 -> 不同阶段抓取任务和要求不同 分成俩部分 
1. 阶段1和4：只抓一个，通过y反映距离，y达到阈值显示已抓取就进入阶段0
2. 阶段2和3：首先通过y反映是否抓取到，然后抓取到的目标分数和需要达到某一阈值才能进入阶段0
"""
def judge_distance_score(y, goal):
    global Y, flag    

    if(y >= Y_thres):
        flag = 0
        print(f"已抓住目标{CLASS_ID[goal]}，准备进入下一工作阶段")
        Y = 0 #刷新临时变量
        return False      
    else:
        Y = y #更新y坐标
        print(f"正在靠近目标{CLASS_ID[goal]}，当前 Y = {Y}")
        return True 
   


def setting(frame,id, score, x_min, y_min, x_max, y_max):
    #设置信息内容
    msg = f'target_message:{id} : {score:.2f}'         
    #信息设置
    frame.draw_string(x_min, y_min, msg, color = image.COLOR_BLUE)
    #标注框设置
    frame.draw_rect(x_min, y_min, x_max-x_min, y_max-y_min, color = image.COLOR_BLUE)


# 此方法功能：在搜寻目标过程中 区分已进入安全区的目标和未进入的
def is_inside(box_a, box_b):
    return box_a[0]>box_b[0] and box_a[1]<box_b[1] and box_a[2]<box_b[2] and box_a[3]<box_b[3]


# 抓取过程结束 此方法功能：判断抓取目标是否已进入安全区，包含阶段切换的逻辑判断 （numbers记录流程次数）
def judge_zone(y):
    global flag, number,scoreflag1#当这里的y达到阈值时，判断scoreflag0的值，使scoreflag1=scoreflag1+scoreflag0，做完这个后给scoreflag0清零，scoreflag1即为累积分数
    if y > Y_thres:
        print("已到达安全区") 
        number += 1                                                                     
        if number > 1 :
            flag = 2
            return

    else:
        print(f"正在靠近安全区，当前距离为 Y={y}")
        return 

def main():
    # 需要用 log(p/(1-p)) 反算阈值，因此阈值不能取 0 或 1。
    if not 0.0 < CONFIDENCE_THRESHOLD < 1.0:
        raise ValueError("CONFIDENCE_THRESHOLD must be between 0 and 1, exclusive")
    print("Loading model: {}".format(MODEL_PATH))
    detector = None
    generic_model = None
    bbox_infos = None
    cls_infos = None

    if USE_GENERIC_NN:
        # 通用 NN 返回原始张量；先核对输入形状、类别数和六路输出布局。
        print("Using generic NN with manual YOLO26 post-processing")
        generic_model = nn.NN(MODEL_PATH, dual_buff=False)
        inputs = generic_model.inputs_info()
        if len(inputs) != 1 or list(inputs[0].shape) != [1, CAMERA_HEIGHT, CAMERA_WIDTH, 3]:
            raise RuntimeError("Set CAMERA_WIDTH/HEIGHT to the model's NHWC input size")
        labels = model_labels(generic_model)
        bbox_infos, cls_infos = generic_output_groups(generic_model)
        # 标签数必须等于分类输出的通道数，否则 class_id 无法正确映射到名称。
        if len(labels) != cls_infos[0].shape[3]:
            raise RuntimeError("MUD label count does not match class output channels")
        input_type = generic_model.extra_info().get("input_type", "rgb")
        if input_type not in ("rgb", "bgr"):
            raise RuntimeError("Unsupported input_type: {}".format(input_type))
        # 摄像头颜色顺序必须与 MUD 的 input_type 一致。
        input_format = (
            image.Format.FMT_RGB888 if input_type == "rgb" else image.Format.FMT_BGR888
        )
        print("Generic detector initialized with {} labels".format(len(labels)))
    else:
        # 仅在设备上的原生 YOLO26 解析器能识别该模型时使用此分支。
        detector = nn.YOLO26(MODEL_PATH, dual_buff=False)
        labels = list(detector.labels)
        input_format = detector.input_format()
        print("YOLO26 detector initialized")

    cam = camera.Camera(CAMERA_WIDTH, CAMERA_HEIGHT, input_format)
    disp = display.Display()

    print("Camera detection started")
    print("Press the device exit key to stop")

    # 收到 app.need_exit() 退出请求时停止；逐帧完成采集、推理、画框和显示。
    while not app.need_exit():
        frame = cam.read()
        # 摄像头暂时没有新帧时跳过本轮，不把空值传给模型。
        if frame is None:
            continue
        # 原生检测器直接返回目标；通用 NN 则需要自行解码六路输出。
        if detector is not None:
            results = detector.detect(
                frame,
                conf_th=CONFIDENCE_THRESHOLD,
                iou_th=IOU_THRESHOLD,
            )
        else:
            results = generic_yolo26_detect(
                generic_model, frame, bbox_infos, cls_infos
            )

        # draw_detection 直接修改当前帧；最后将带框的帧显示到设备屏幕。
        detection_count = 0
        #length = len(results)
        #print("当前检测到{}个目标\n".format(length))
        #print("Results: {}".format(results))
        #print(f"目标\t置信度\t当前帧率\t")
        
        current_phase = None #当前阶段
        default_phase = "PH1" #默认阶段
        #阶段保护设置 防止死机
        if current_phase == None or current_phase not in Phase_config or flag == 1:
            print(f"-----\n检测开始，已将当前阶段切换为第 1 阶段{default_phase}！\n-----")
            current_phase = default_phase 
        

        #阶段自动转换设置 （flag） | 注意阶段切换的条件【PH1，PH4】->抓一个->PH0 【PH2，PH3】->分数达到阈值->PH0
        match flag:
            case 2:
                current_phase = "PH2" 
                print(f"-----\n检测开始，已将当前阶段切换为第 2 阶段{current_phase}！\n-----")    
            case 0:
                #PH0阶段转换
                current_phase = "PH0" 
                print("-----\n目标抓取任务完成，已将当前阶段切换为PH0!\n-----")
    
        phase_cfg = Phase_config[current_phase] #保存当前阶段的信息
        """
        阶段切换内容
        """
        weights = phase_cfg["priority_ID"] # 保存每个阶段设置的目标优先级
        Objects = phase_cfg["target_ID"] # 保存每个阶段应检测的目标
        #保存当前检测到的所有目标
        all = []
        #保存当前需要抓取的物资
        candidates0 = []
        #暂存当前检测到的目标中不在安全区的目标
        candidates1 = []
        #保存安全区的信息
        zones_all = []
        #保存安全区的坐标信息
        zones_xy = []
        for result in results:
            # 画框
            #class_name, score = draw_detection(frame, result, labels)

            x_min = int(get_result_value(result, "x", 0))
            y_min = int(get_result_value(result, "y", 0))
            w = int(get_result_value(result, "w", 0))
            h = int(get_result_value(result, "h", 0))
            x_max = x_min + w
            y_max = y_min + h
            class_id = int(get_result_value(result, "class_id", 0))
            score = float(get_result_value(result, "score", 0.0))
            
            # 如果目标不在当前阶段应检测的范围内，则跳过
            detection_count += 1
            if class_id not in Objects:
                continue
            all.append((class_id, x_min, y_min, x_max, y_max, score))
            
            #将安全区与其它目标信息分别处理 frames和zones保存安全区的信息 candidates保存目标信息
            if class_id == 6:
                zones_all.append((class_id, x_min, y_min, x_max, y_max, score))
                zones_xy.append((x_min, y_min, x_max, y_max))

            else:

                #判断检测到的目标是否在安全区内
                if phase_cfg["filter_frames"] and len(zones_xy) > 0:
                    is_outside = not any(is_inside((x_min, y_min, x_max, y_max), f) for f in zones_xy )
                    if is_outside:
                        candidates1.append((class_id, x_min, y_min, x_max, y_max, score))
                else:
                    candidates1.append((class_id, x_min, y_min, x_max, y_max, score))  
                    
        #目标选择适用于所有阶段
        candidates0 = [new_list for new_list in candidates1 if new_list[2] <= Y_thres] #筛选已抓取的目标 
        candidates0.sort(key=lambda x: (weights.get(x[0],float("inf")), -x[4])) # 将candidates里面的元素 先按照权重进行排序， 当权重相同时再根据y_max进行排序
        # 安全区按照y_max排序
        zones_all.sort(key=lambda x: -x[4])
        
        send_data = struct.pack(">4H", 3, 20, 3, 20) #初始化发送数据
        
        if  current_phase in "PH0":
            print(f"-------\n当前阶段为{current_phase}\n-------")  
            # 判断当前画面是否识别到安全区
            if zones_all == []:
                print("正在寻找安全区！")
            else:
                selected1 = zones_all[0]
                cls1_id, x1_min, y1_min, x1_max, y1_max, score1= selected1
                
                
                print(f"x1_min: {x1_min}, y1_min: {y1_min}, x1_max: {x1_max}, y1_max: {y1_max}, score: {score1:.2f}")
                
                goal1 = cls1_id
                # 计算安全区的中心坐标
                center_x1 = int(round((x1_max + x1_min) / 2 ))
                center_y1 = int(round((y1_max + y1_min) / 2 ))

                center_x1_zhengshu = center_x1 // 100
                center_x1_yushu = center_x1 % 100
                center_y1_zhengshu = center_y1 // 100
                center_y1_yushu = center_y1 % 100

                send_data = struct.pack(">4H", center_x1_zhengshu, center_x1_yushu, center_y1_zhengshu, center_y1_yushu)

                setting(frame, goal1, score1, x1_min, y1_min, x1_max, y1_max)  
                judge_zone(y1_min)
                        

        elif current_phase in ["PH1", "PH2"]:
            #抓取前处理目标信息
            if candidates0 == []:
                print("正在寻找目标")
            else:
                selected0 = candidates0[0]
                cls0_id, x0_min, y0_min, x0_max, y0_max, score0= selected0
                goal0 = cls0_id
                if goal0 in Objects: #判断当前目标是否属于当前阶段需检测的目标  
                    print(f"-------\n当前阶段为{current_phase}\n-------")    
                    print(f"当前的目标是：{CLASS_ID[goal0]}")

                    center_x0 = int(round((x0_max + x0_min) / 2 ))
                    center_y0 = int(round((y0_max + y0_min) / 2 ))
                    center_x0_zhengshu = center_x0 // 100
                    center_x0_yushu = center_x0 % 100
                    center_y0_zhengshu = center_y0 // 100
                    center_y0_yushu = center_y0 % 100
                    send_data = struct.pack(">4H", center_x0_zhengshu, center_x0_yushu, center_y0_zhengshu, center_y0_yushu)
                    #send_data = f"W{x0_min} {y0_min} {x0_max} {y0_max} 0L"
                    if judge_distance_score(y0_min, goal0):
                        setting(frame, goal0, score0, x0_min, y0_min, x0_max, y0_max)
                else:
                    print("!!!!!目标检测错误!!!!!\n!!!!!正在寻找新的目标!!!!!")        

              # 发送数据
        if send_data is not None:
            print(f"发送数据 : {send_data}")
            serial.write(send_data)
            print("send success")
        else:
            pass  
        disp.show(frame)


if __name__ == "__main__":
    main()
