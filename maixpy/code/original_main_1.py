from maix import camera, display, image, nn, app, time, pwm, pinmap

from maix import uart #串口
import struct
import sys
sys.path.append('/root/exam')

device = "/dev/ttyS0"
serial = uart.UART(device,9600) #串口配置

pwm_id = 7
pinmap.set_pin_function("A19", "PWM7") #使用MaixCAM的pwm7和A19引脚



#设置检测模型
detector = nn.YOLO11(model="/root/CR_demo/my_mud.mud",dual_buff = True)
#创建摄像机实例
cam = camera.Camera(detector.input_width(), detector.input_height(), detector.input_format())
#创建检测实例
disp = display.Display() 

#print("编号\t分数\t上位机位置信息\t下位机位置信息\t帧率")

#类ID映射表
CLASS_ID={
    0 : "ball_red", # 5
    1 : "cylinder_red", #  10 
    2 : "ball_black", # 5
    3 : "cylinder_yellow", # 10
    4 : "tri-pyramid_blue", # 20
    5 : "cube_blue", # 15
    6 : "zone" #安全区
}

#分数映射表
SCORE_ID={
     0: 5, # 5
     1: 10, #  10 
     2: 5, # 5
     3: 10, # 10
     4: 20, # 20
     5: 15, # 15
}




#坐标转换（用于上位机与下位机间通信）
def convert_x_y(x,y,w,h):
    x2 = int(-320 + x + w/2)
    y2 = int(320 - y - h/2)
    return int(x), int(y)


"""
此方法功能：反映抓取过程 判断抓取到的目标是否符合要求 -> 不同阶段抓取任务和要求不同 分成俩部分 
1. 阶段1和4：只抓一个，通过y反映距离，y达到阈值显示已抓取就进入阶段0
2. 阶段2和3：首先通过y反映是否抓取到，然后抓取到的目标分数和需要达到某一阈值才能进入阶段0
"""
def judge_distance_score(y, goal):
    global Y, flag , get_score, get_id    
    if current_phase in ["PH1", "PH4"]:
        if(y >= Y_thres):
            flag = 0
            print(f"已抓住目标{CLASS_ID[goal]}，准备进入下一工作阶段")
            Y = 0 #刷新临时变量
            return False      
        else:
            Y = y #更新y坐标
            print(f"正在靠近目标{CLASS_ID[goal]}，当前 Y = {Y}")
            return True 
    elif current_phase in ["PH2", "PH3"]:
        #此if-else用于防止已抓取到的目标被重复检测抓取
        if(y>=Y_thres and goal not in get_id):
            print(f"已抓住目标{CLASS_ID[goal]}")
            get_score += SCORE_ID[goal]#将抓取目标的分数记录下来
            get_id.append(goal) #将抓取目标的id记录下来
            if get_score >= 15: #当分数达到阈值时，进行阶段转换
                flag = 0
                Y = 0 #刷新临时变量
                print(f"现已抓住目标{get_id}，准备进入下一工作阶段")
                print(f"当前抓取目标的分数总和为{get_score}")
                get_score = 0 #清零分数
                get_id = [] #清零id
                return False
            else:
                print("当前分数不达标，继续抓取目标")
                Y = 0 #刷新临时变量
                return True
        elif goal in get_id:
            print(f"{CLASS_ID[goal]}已抓取，请切换下一目标")
            return True
        else:
            Y = y #更新y坐标
            print(f"正在靠近目标{CLASS_ID[goal]}，当前 Y = {Y}")
            return True  
    """
    else:
        print(f"正在远离目标{CLASS_ID[cls0_id]}，当前 Y = {Y}")
        return True   
    """

# 抓取过程结束 此方法功能：判断抓取目标是否已进入安全区，包含阶段切换的逻辑判断 （numbers记录流程次数）
def judge_zone(y):
    global flag, number,scoreflag1#当这里的y达到阈值时，判断scoreflag0的值，使scoreflag1=scoreflag1+scoreflag0，做完这个后给scoreflag0清零，scoreflag1即为累积分数
    if y > Y_thres:
        print("已到达安全区") 
        number += 1                                                                     
        if number < 2 :
            flag = 1
            return
        elif number == 2:
            flag = 2
            return
        elif number == 3:
            flag = 3
        else:
            flag = 4 
    else:
        print(f"正在靠近安全区，当前距离为 Y={y}")
        return 
# 此方法功能：在搜寻目标过程中 区分已进入安全区的目标和未进入的
def is_inside(box_a, box_b):
    return box_a[0]>box_b[0] and box_a[1]<box_b[1] and box_a[2]<box_b[2] and box_a[3]<box_b[3]
# 此方法功能：总结标注和标注框 减少代码的重复性使用 使代码更具有稳健性
def setting(id, score, x_min, y_min, x_max, y_max):
    #设置信息内容
    msg = f'target_message:{id} : {score:.2f}'         
    #信息设置
    img.draw_string(x_min, y_min, msg, color = image.COLOR_BLUE)
    #标注框设置
    img.draw_rect(x_min, y_min, x_max-x_min, y_max-y_min, color = image.COLOR_BLUE)


#阶段配置表 罗列了各个阶段的检测目标（targit_ID），抓取目标的优先级（priority_ID），以及判断是否需要过滤已在安全区中的目标（priority_ID）
Phase_config = {
    "PH1":{
            "target_ID" : [0, 2], # 目标：5 | 优先级->距离 | 执行2次 | -(抓1个)->PH0->PH1-(抓1个)->PH0->PH2 
            "filter_frames" : False,
            "priority_ID": {0: 0, 2: 0},
    },
    "PH2":{
            "target_ID" : [0, 1, 2, 3], # 目标：5，10 | 优先级->距离 | 执行1次 | -(get_score>=15)->PH0->PH3
            "filter_frames" : False,
            "priority_ID" : {1: 0, 3: 0, 0: 0, 2: 0 },
    },
    "PH3":{
            "target_ID" : [0, 1, 2, 3, 5], # 目标：5，10，15 | 优先级->分数 | 执行1次 | -(get_score>=15)>PH0->PH4
            "filter_frames" : True,
            "priority_ID" : {5: 0, 1: 1, 3: 1, 0: 2, 2: 2 },
    },
    "PH4":{
            "target_ID" : [0, 1, 2, 3, 4, 5], #目标：5，10.15，20 | 优先级->分数 | 执行至最后 | -(抓1个)>PH0->PH4
            "filter_frames" : True,
            "priority_ID": {4: 0, 5: 1, 1: 2, 3: 2, 0: 3, 2: 3},
    },
    "PH0":{
            "target_ID" : [6], # 目标：安全区
            "filter_frames" : False,
            "priority_ID":{6: 0},
    },

} 

#以下皆为全局变量
current_phase = None #当前阶段
default_phase = "PH2" #默认阶段


Y = 0 # 初始化y 用于临时保存当下y坐标
Y_thres = 400 # y坐标阈值 用于判断目标是否达到已被抓取的标准

get_score = 0 # 用于记录当前抓取目标的分数
get_id = [] # 用于记录当前抓取目标的id

flag = 1 # 阶段转换标志
number = 0 # 记录从执行抓取到安全区一整个流程的次数

#进入获取图像的循环操作
while not app.need_exit():
    #阶段保护设置 防止死机
    if current_phase == None or current_phase not in Phase_config or flag == 1:
        print(f"-----\n检测开始，已将当前阶段切换为第 1 阶段{default_phase}！\n-----")
        current_phase = default_phase 
    

    #阶段自动转换设置 （flag） | 注意阶段切换的条件【PH1，PH4】->抓一个->PH0 【PH2，PH3】->分数达到阈值->PH0
    match flag:
        case 2:
            current_phase = "PH2" 
            print(f"-----\n检测开始，已将当前阶段切换为第 2 阶段{current_phase}！\n-----")
        case 3:
            current_phase = "PH3" 
            print(f"-----\n检测开始，已将当前阶段切换为第 3 阶段{current_phase}！\n-----")    
        case 4:
            current_phase = "PH4" 
            print(f"-----\n检测开始，已将当前阶段切换为第 4 阶段{current_phase}！\n-----")
        case 0:
            #PH0阶段转换
            current_phase = "PH0" 
            print("-----\n目标抓取任务完成，已将当前阶段切换为PH0!\n-----")

    
    frames=[] #安全区完整信息记录
    zones=[]#安全区坐标记录
    candidates0=[] #记录暂存
    candidates=[] #目标抓取坐标记录（会持续更新）
    all = []
    '''
    goodx = 0
    goody = 0
    '''
    img = cam.read() #读取图像

    phase_cfg = Phase_config[current_phase] #保存当前阶段的信息
    
    """
    阶段切换内容
    """
    weights = phase_cfg["priority_ID"] # 保存每个阶段设置的目标优先级
 
    Objects = phase_cfg["target_ID"] # 保存每个阶段应检测的目标
    
    objs = detector.detect(img, conf_th = 0.8, iou_th = 0.25) #保存所有达到置信度阈值的目标
    # 使用循环 处理所有检测到的目标信息
    for obj in objs:
        #临时记录每个目标的id 坐标 置信度
        cls_id = obj.class_id
        x_min = int(obj.x)
        y_min = int(obj.y)
        x_max = int(obj.w + obj.x)
        y_max = int(obj.h + obj.y)
        score = obj.score
    
        all.append((cls_id, x_min, y_min, x_max, y_max, score))# 保存当前检测到的所有已处理的目标信息 用于后续对结果进行比对

        #将安全区与其它目标信息分别处理 frames和zones保存安全区的信息 candidates保存目标信息
        if cls_id == 6:
            frames.append((cls_id, x_min, y_min, x_max, y_max, score))
            zones.append((x_min, y_min, x_max, y_max))
            img.draw_rect(x_min, y_min, x_max-x_min, y_max-y_min,image.Color.from_rgb(255,0,0),2)#安全区和球的标注框用不同颜色
        else:
            img.draw_rect(x_min, y_min, x_max-x_min, y_max-y_min,image.Color.from_rgb(0,255,0),2)
            #判断抓取目标是否在安全区内
            if phase_cfg["filter_frames"]:
                is_outside = not any(is_inside((x_min, y_min, x_max, y_max), f) for f in zones )
                if is_outside:
                    candidates0.append((cls_id, x_min, y_min, x_max, y_max, score))
            else:
                candidates0.append((cls_id, x_min, y_min, x_max, y_max, score))        

    send_data = None
    
    #目标选择适用于所有阶段
    candidates = [new_list for new_list in candidates0 if new_list[2] <= Y_thres] #筛选已抓取的目标 
    candidates.sort(key=lambda x: (weights.get(x[0],float("inf")), -x[4])) # 将candidates里面的元素 先按照权重进行排序， 当权重相同时再根据y_max进行排序
    #注意：抓取过程前->候选目标由y_max来反映距离->定位并选中抓取对象 | 在抓取过程中->根据y_min来反应当前的距离
    frames.sort(key=lambda x: -x[4])
    
    #阶段选择 将寻找安全区和寻找抓取目标的时期进行分类
    if  current_phase in "PH0":
        print(f"-------\n当前阶段为{current_phase}\n-------")  
        # 判断当前画面是否识别到安全区
        if frames == []:
            print("正在寻找安全区！")
        else:
            selected1 = frames[0]
            cls1_id, x1_min, y1_min, x1_max, y1_max, score1= selected1
            goal1 = cls1_id
            #寻找安全区 将安全区  所在位置通过convert_x_y方法转换成下位机能够正确读取的坐标信息并保存
            goodx, goody = convert_x_y(x1_min, y1_min, x1_max - x1_min, y1_max - y1_min)
            send_data = f"W{goody} {goodx} 0L"
            setting(goal1, score1, x1_min, y1_min, x1_max, y1_max)
            judge_zone(y1_min)
                    

    elif current_phase in ["PH1", "PH2", "PH3", "PH4",]:
        #抓取前处理目标信息
        if candidates == []:
            print("正在寻找目标")
        else:
            selected0 = candidates[0]
            cls0_id, x0_min, y0_min, x0_max, y0_max, score0= selected0
            goal0 = cls0_id
            if goal0 in Objects: #判断当前目标是否属于当前阶段需检测的目标  
                print(f"-------\n当前阶段为{current_phase}\n-------")    
                print(f"当前的目标是：{CLASS_ID[goal0]}")
                #抓取中 将目标所在位置通过convert_x_y方法转换成下位机能够正确读取的坐标信息并保存
                goodx, goody = convert_x_y(x0_min, y0_min, x0_max - x0_min, y0_max - y0_min)
                send_data = f"W{goody} {goodx} 0L"
                if judge_distance_score(y0_min, goal0):
                    setting(goal0, score0, x0_min, y0_min, x0_max, y0_max)
            else:
                print("!!!!!目标检测错误!!!!!\n!!!!!正在寻找新的目标!!!!!")
                
                
      # 发送数据
    if send_data is not None:
        print(f"发送数据 : {send_data}")
        serial.write_str(send_data)
    else:
        pass            
    
    disp.show(img)
    time.sleep(0.5)
"""
完成情况：
1. 完成了分数和id的映射关系
2. 实现了由分数决定阶段转换的逻辑
3. 在筛选抓取目标的过程中通过y_min与y_thres的比较解决了对于已经抓取过的目标 是否会被重复检测
4. 实现了串口通信
"""