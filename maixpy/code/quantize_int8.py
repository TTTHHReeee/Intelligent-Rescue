from pathlib import Path

import cv2
import numpy as np
import onnx
import onnxruntime as ort
from onnxruntime.quantization import (
    CalibrationDataReader,
    CalibrationMethod,
    QuantFormat,
    QuantType,
    quantize_static,
)


# ==================== 全局配置 ====================
INPUT_ONNX = Path(r"D:\桌面\工训\maixpy\code\runs\detect\train-2\weights\best.onnx")
OUTPUT_ONNX = Path(r"D:\桌面\工训\maixpy\code\runs\detect\train-2\weights\best_int8.onnx")
CALIBRATION_DIR = Path(r"D:\桌面\工训\datasets\images\train")

IMAGE_SIZE = 640
CALIBRATION_IMAGE_COUNT = 500

# Resolve paths from this script so the code does not depend on the encoding
# of a hard-coded Chinese absolute path.
CODE_DIR = Path(__file__).resolve().parent
PROJECT_DIR = CODE_DIR.parent.parent
INPUT_ONNX = CODE_DIR / "runs" / "detect" / "train-2" / "weights" / "best.onnx"
OUTPUT_ONNX = CODE_DIR / "runs" / "detect" / "train-2" / "weights" / "best_int8.onnx"
CALIBRATION_DIR = PROJECT_DIR / "datasets" / "images" / "train"
# ==================================================


class ImageCalibrationDataReader(CalibrationDataReader):
    def __init__(self, model_path, image_dir):
        session = ort.InferenceSession(
            str(model_path),
            providers=["CPUExecutionProvider"],
        )

        self.input_name = session.get_inputs()[0].name
        self.image_paths = sorted(
            path
            for path in image_dir.iterdir()
            if path.suffix.lower() in {".jpg", ".jpeg", ".png", ".bmp"}
        )[:CALIBRATION_IMAGE_COUNT]
        self.index = 0

        if not self.image_paths:
            raise FileNotFoundError("没有找到校准图片: {}".format(image_dir))

    def get_next(self):
        if self.index >= len(self.image_paths):
            return None

        image_path = self.image_paths[self.index]
        self.index += 1

        # cv2.imread() may fail on Windows paths containing Chinese characters.
        image_buffer = np.fromfile(str(image_path), dtype=np.uint8)
        image = cv2.imdecode(image_buffer, cv2.IMREAD_COLOR)
        if image is None:
            return self.get_next()

        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        image = cv2.resize(image, (IMAGE_SIZE, IMAGE_SIZE))
        image = image.astype(np.float32) / 255.0
        image = np.transpose(image, (2, 0, 1))
        image = np.expand_dims(image, axis=0)

        return {self.input_name: image}


def patch_shape_inference_for_windows():
    """Work around onnx 1.17 not writing infer_shapes_path output on Windows."""
    def infer_shapes_path(input_path, output_path=None, **kwargs):
        model = onnx.load(str(input_path))
        inferred_model = onnx.shape_inference.infer_shapes(model)
        target_path = output_path or input_path
        onnx.save(inferred_model, str(target_path))

    onnx.shape_inference.infer_shapes_path = infer_shapes_path


def main():
    if not INPUT_ONNX.exists():
        raise FileNotFoundError("模型不存在: {}".format(INPUT_ONNX))

    reader = ImageCalibrationDataReader(
        INPUT_ONNX,
        CALIBRATION_DIR,
    )

    patch_shape_inference_for_windows()

    OUTPUT_ONNX.parent.mkdir(parents=True, exist_ok=True)

    quantize_static(
        model_input=str(INPUT_ONNX),
        model_output=str(OUTPUT_ONNX),
        calibration_data_reader=reader,
        quant_format=QuantFormat.QDQ,
        activation_type=QuantType.QInt8,
        weight_type=QuantType.QInt8,
        per_channel=True,
        calibrate_method=CalibrationMethod.MinMax,
    )

    print("INT8 模型已生成:")
    print(OUTPUT_ONNX)
    print("原始大小: {:.2f} MB".format(INPUT_ONNX.stat().st_size / 1024 / 1024))
    print("INT8 大小: {:.2f} MB".format(OUTPUT_ONNX.stat().st_size / 1024 / 1024))


if __name__ == "__main__":
    main()
