from ultralytics import YOLO

def train_yolo_model():
    # 设置训练参数
    model = YOLO("D:/桌面/工训/maixpy/code/runs/detect/train-2/weights/best.pt")  # 使用预训练的 YOLOv8n 模型
    data_path = "D:/桌面/工训/datasets_2/data.yaml"  # 数据集路径
    epochs = 200  # 训练轮数
    batch_size = 32  # 批量大小

    # 开始训练
    model.train(data=data_path, epochs=epochs, batch=batch_size, imgsz=640, device=0)  # 使用 GPU 进行训练，图像大小为 640x640
    model.export(format="onnx", imgsz=640)  # 导出为 ONNX 格式，图像大小为 640x640
def export_yolo_model():
    # 导出为 ONNX 格式
    model = YOLO("runs/detect/train-6/weights/best.pt")  # 使用训练好的模型权重
    model.export(format="onnx", imgsz=640, opset=17, batch=1, dynamic=False, simplify=True, nms=False)  # 导出为 ONNX 格式，图像大小为 640x640
    
if __name__ == "__main__":
    #train_yolo_model()
    export_yolo_model()