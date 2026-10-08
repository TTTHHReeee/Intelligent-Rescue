from maix import camera, display, image, nn, app, pwm, time, pinmap
"""
from maix import uart #串口
import struct
import sys
sys.path.append('/root/exam')
"""
detector = nn.YOLOv5(model="/root/models/113mode/model_184258.mud")
#启动摄像头，串口
"""
cam = camera.Camera(detector.input_width(), detector.input_height(), detector.input_format())
dis = display.Display()
device = "/dev/ttyS0"
serial = uart.UART(device,9600) #串口配置
"""
# 初始化全局变量
current_phase = None  # 当前阶段标识
default_phase = "W1L"  # 默认阶段
#舵机部分
"""
SERVO_PERIOD = 50     # 50Hz 20ms
SERVO_MIN_DUTY = 2.5  # 2.5% -> 0.5ms
SERVO_MAX_DUTY = 12.5  # 12.5% -> 2.5ms
pwm_id = 7
pinmap.set_pin_function("A19", "PWM7") #使用MaixCAM的pwm7和A19引脚
"""
#控制舵机的旋转角度
"""
def angle_to_duty(percent):
    return (SERVO_MAX_DUTY - SERVO_MIN_DUTY) * percent / 100.0 + SERVO_MIN_DUTY
out = pwm.PWM(pwm_id, freq=SERVO_PERIOD, duty=angle_to_duty(80), enable=True)
"""
# 类ID映射表
CLASS_ID_MAP = {
    0: "black_x",       # 黑十字
    1: "red_frame",     # 红区
    2: "blackball",     # 黑球
    6: "blue_frame",    # 蓝区
    7: "redball",       # 红球
    8: "yellowball",    # 黄球
    3: "blueball"       #蓝球
}

# 阶段配置参数（关键修改：移除min_confidence配置）
PHASE_CONFIG = { #filter_frames: 是否对输入帧做过滤处理
    #阶段1——第一次
    "W1L": {
        "target_ids": [3], # 目标：蓝球         
        "filter_frames": False,
        "priority_weights": {3: 0}, # 优先级：蓝球  
    },
    #阶段2——第二次
    "W2L": {
        "target_ids": [1], # 目标：红区
        "filter_frames": False,
        "priority_weights": {1: 0},   
    },
    #阶段3——第三次
    "W3L": {
        "target_ids": [8, 2], # 目标：黄球、黑球
        "filter_frames": True,
        "priority_weights": {8: 0, 2: 1},  # 优先级：黄球、黑球
    },
    #阶段4——第九次
    "W9L": {
        "target_ids": [8, 2, 3], # 目标：黄球、黑球、蓝球
        "filter_frames": True,
        "priority_weights": {8: 0, 2: 1, 3: 2},  # 优先级：黄球、黑球、蓝球
    }
}



# 辅助函数
def xy(x, y, w, h):
    """坐标转换函数"""
    goodx = x + w/2
    goody = 448 - (y + h/2)
    return int(goodx), int(goody)

def is_inside(box_a, box_b):#box_b是否包含box_a
    """矩形包含判断"""
    return (box_a[0] >= box_b[0] and 
            box_a[1] >= box_b[1] and 
            box_a[2] <= box_b[2] and 
            box_a[3] <= box_b[3])

def get_confidence_attr(obj): #获取模型的置信度
    """兼容不同模型版本的置信度属性"""
    #鉴于使用的模型版本不同，置信度属性名可能不同，故使用hasattr进行判断
    return obj.confidence if hasattr(obj, 'confidence') else obj.prob

# 主程序入口
while not app.need_exit():
    img = cam.read()
    #out.duty(angle_to_duty(77))
    
    # 串口通信处理（保持原逻辑）
    """
    data1 = serial.read()
    if data1:
        str_data1 = data1.decode('utf-8').strip()
        print(f"Received command: {str_data1}")
        if str_data1 in PHASE_CONFIG:
            current_phase = str_data1
    else:
        pass
    """
    #if current_phase in ["W1L","W3L","W9L"]

    # 阶段有效性保护
    if current_phase is None or current_phase not in PHASE_CONFIG:
        print(f"Phase invalid, switching to {default_phase}")
        current_phase = default_phase
    
    # 主目标检测
    red_frames = [] # 存储红框坐标
    candidates = [] # 存储候选球类坐标
    phase_cfg = PHASE_CONFIG[current_phase]
    frames = [] # 存储框架类坐标
    for obj in detector.detect(img, conf_th = 0.5, iou_th = 0.45):
        cls_id = obj.class_id
        x_min = int(obj.x)
        y_min = int(obj.y)
        x_max = int(obj.x + obj.w)
        y_max = int(obj.y + obj.h)
        '''
        检查球是否完全进入框架区域
        '''  
        # 框架类处理（保持原逻辑）
        if cls_id in [1, 6] and obj.score>0.5:
            frames.append( (x_min, y_min, x_max, y_max) ) #增加框架类的坐标记录
            img.draw_rect(x_min, y_min, x_max-x_min, y_max-y_min, 
                        image.Color.from_rgb(0,255,0), 2)
            if cls_id ==6 and obj.score>0.7:
                red_frames.append( (x_min, y_min, x_max, y_max) )
                img.draw_rect(x_min, y_min, x_max-x_min, y_max-y_min, 
                        image.Color.from_rgb(0,0,255), 2)
        
        # 球类处理（移除置信度筛选）
        if cls_id in phase_cfg["target_ids"] and obj.score>0.8:
            if phase_cfg["filter_frames"]:
                is_outside = not any(is_inside( (x_min,y_min,x_max,y_max), f ) for f in frames)
                if is_outside:
                    candidates.append( (cls_id, x_min, y_min, x_max, y_max) )
            else:
                candidates.append( (cls_id, x_min, y_min, x_max, y_max) )

    send_data = None
    
    # W2L阶段处理（按Y轴降序排序）
    if current_phase == "W2L":
        sorted_frames = sorted(red_frames, key=lambda x:-x[1] )  # 改为按Y轴降序排列
        if sorted_frames:
            frame = sorted_frames[0]
            x_min, y_min, x_max, y_max = frame
            goodx, goody = xy(x_min, y_min, x_max - x_min, y_max - y_max)
            send_data = f"W{goody} {goodx} 0L"

    elif current_phase in ["W1L","W3L", "W9L"]:
        weights = phase_cfg["priority_weights"]
        # 按优先级权重排序
        candidates.sort(key=lambda x: weights.get(x[0], float('inf')))
        
        if candidates:
            selected = candidates[0]
            cls_id, x_min, y_min, x_max, y_max = selected
            img.draw_rect(x_min, y_min, x_max-x_min, y_max-y_min, 
                        image.Color.from_rgb(255,0,0), 2)
            goodx, goody = xy(x_min, y_min, x_max - x_min, y_max - y_max)
            send_data = f"W{goody} {goodx} 0L"
    else:
        
        pass
    
    #Fallback到黑十字
    if send_data is None:
        objs = detector.detect(img, conf_th = 0.8, iou_th = 0.45)  
        for obj in objs:
            if obj.class_id == 0:
                x_min = int(obj.x)
                y_min = int(obj.y)
                x_max = int(obj.x + obj.w)
                y_max = int(obj.y + obj.h)
                img.draw_rect(x_min, y_min, x_max-x_min, y_max-y_min, 
                            image.Color.from_rgb(0,0,255), 2)
                goodx, goody = xy(x_min, y_min, x_max-x_min, y_max-y_min)
                send_data = f"W{goody} {goodx} 1L"
    
    # 发送数据
    if send_data is not None:
        print(f"Sending: {send_data}")
        serial.write_str(send_data)
    else:
        pass
    
    dis.show(img)
    

