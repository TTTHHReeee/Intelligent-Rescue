"""MaixCAM2 camera + YOLO26 detection demo.

The generic NN backend is useful with MaixPy runtimes whose YOLO26 wrapper
cannot distinguish bbox and class outputs when the model has exactly four
classes.  The MUD file still contains the normal six YOLO26 output tensors.
"""

import math

import numpy as np

from maix import app, camera, display, image, nn, tensor, time


# ==================== User-adjustable settings ====================
MODEL_PATH = "/root/my_model/model_9540.mud"
# Use the existing six-output model without the native four-class parser.
# Set False only when the device's nn.YOLO26 parser supports this model.
USE_GENERIC_NN = True
# Keep camera dimensions equal to the model input to avoid resize/padding drift.
CAMERA_WIDTH = 640
CAMERA_HEIGHT = 640
CONFIDENCE_THRESHOLD = 0.50
IOU_THRESHOLD = 0.45
# YOLO26 one-to-one heads do not need NMS; IOU_THRESHOLD is for API compatibility.
PRINT_DETECTIONS = False

BOX_COLOR = image.COLOR_RED
TEXT_COLOR = image.COLOR_GREEN
TEXT_SCALE = 1.0
BOX_THICKNESS = 1

MODEL_MEAN = [0.0, 0.0, 0.0]
MODEL_SCALE = [1.0 / 255.0, 1.0 / 255.0, 1.0 / 255.0]
# ================================================================


def get_result_value(result, name, default=None):
    """Read a detection field from either an object or a dictionary."""
    if isinstance(result, dict):
        return result.get(name, default)
    return getattr(result, name, default)


def draw_detection(frame, result, labels):
    """Draw one detector result on a MaixPy image."""
    x = int(get_result_value(result, "x", 0))
    y = int(get_result_value(result, "y", 0))
    w = int(get_result_value(result, "w", 0))
    h = int(get_result_value(result, "h", 0))
    class_id = int(get_result_value(result, "class_id", 0))
    score = float(get_result_value(result, "score", 0.0))

    if 0 <= class_id < len(labels):
        class_name = str(labels[class_id])
    else:
        class_name = "class_{}".format(class_id)

    frame.draw_rect(
        x,
        y,
        w,
        h,
        color=BOX_COLOR,
        thickness=BOX_THICKNESS,
    )

    text = "{} {:.1f}%".format(class_name, score * 100.0)
    text_y = max(0, y - 24)
    frame.draw_string(
        x,
        text_y,
        text,
        color=TEXT_COLOR,
        scale=TEXT_SCALE,
    )

    return class_name, score


def model_labels(model):
    """Read labels from MUD metadata on different MaixPy builds."""
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
    """Find the three bbox and three class heads in a YOLO26 MUD model."""
    bbox = []
    cls = []

    for info in model.outputs_info():
        name = str(info.name)
        shape = list(info.shape)
        if len(shape) != 4:
            continue
        lower_name = name.lower()
        if "one2one_cv2" in lower_name:
            bbox.append(info)
        elif "one2one_cv3" in lower_name:
            cls.append(info)

    key = lambda info: int(info.shape[1]) * int(info.shape[2])
    bbox.sort(key=key, reverse=True)
    cls.sort(key=key, reverse=True)

    if len(bbox) != 3 or len(cls) != 3:
        raise RuntimeError(
            "Expected 3 bbox and 3 cls heads, got {} bbox and {} cls".format(
                len(bbox), len(cls)
            )
        )

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
    """Numerically safe sigmoid for class logits."""
    value = float(value)
    if value >= 0.0:
        exp_value = math.exp(-value)
        return 1.0 / (1.0 + exp_value)
    exp_value = math.exp(value)
    return exp_value / (1.0 + exp_value)


def generic_yolo26_detect(model, frame, bbox_infos, cls_infos):
    """Run and decode the six raw YOLO26 NHWC output tensors."""
    if frame.width() != CAMERA_WIDTH or frame.height() != CAMERA_HEIGHT:
        raise RuntimeError("Camera frame size differs from the configured model input")
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
    logit_threshold = math.log(CONFIDENCE_THRESHOLD / (1.0 - CONFIDENCE_THRESHOLD))
    for bbox_info, cls_info in zip(bbox_infos, cls_infos):
        bbox_array = tensor.tensor_to_numpy_float32(
            outputs[bbox_info.name], copy=False
        )[0]
        cls_array = tensor.tensor_to_numpy_float32(
            outputs[cls_info.name], copy=False
        )[0]

        grid_height = int(bbox_info.shape[1])
        grid_width = int(bbox_info.shape[2])
        stride_x = float(CAMERA_WIDTH) / grid_width
        stride_y = float(CAMERA_HEIGHT) / grid_height
        if tuple(bbox_array.shape) != tuple(bbox_info.shape[1:]):
            raise RuntimeError("Unexpected bbox tensor layout")
        if tuple(cls_array.shape) != tuple(cls_info.shape[1:]):
            raise RuntimeError("Unexpected class tensor layout")

        # Filter all cells in NumPy; only decode candidates above threshold.
        class_ids = np.argmax(cls_array, axis=-1)
        logits = np.max(cls_array, axis=-1)
        rows, cols = np.nonzero(np.isfinite(logits) & (logits >= logit_threshold))
        for grid_y, grid_x in zip(rows, cols):
            distances = bbox_array[grid_y, grid_x]
            if not np.all(np.isfinite(distances)):
                continue
            left, top, right, bottom = (float(v) for v in distances)
            center_x = (int(grid_x) + 0.5) * stride_x
            center_y = (int(grid_y) + 0.5) * stride_y
            # Clip both corners, rather than clipping the origin and retaining
            # a width/height that belonged to an off-screen box.
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

    return results


def main():
    if not 0.0 < CONFIDENCE_THRESHOLD < 1.0:
        raise ValueError("CONFIDENCE_THRESHOLD must be between 0 and 1, exclusive")
    print("Loading model: {}".format(MODEL_PATH))
    detector = None
    generic_model = None
    bbox_infos = None
    cls_infos = None

    if USE_GENERIC_NN:
        print("Using generic NN with manual YOLO26 post-processing")
        generic_model = nn.NN(MODEL_PATH, dual_buff=False)
        inputs = generic_model.inputs_info()
        if len(inputs) != 1 or list(inputs[0].shape) != [1, CAMERA_HEIGHT, CAMERA_WIDTH, 3]:
            raise RuntimeError("Set CAMERA_WIDTH/HEIGHT to the model's NHWC input size")
        labels = model_labels(generic_model)
        bbox_infos, cls_infos = generic_output_groups(generic_model)
        if len(labels) != cls_infos[0].shape[3]:
            raise RuntimeError("MUD label count does not match class output channels")
        input_type = generic_model.extra_info().get("input_type", "rgb")
        if input_type not in ("rgb", "bgr"):
            raise RuntimeError("Unsupported input_type: {}".format(input_type))
        input_format = (
            image.Format.FMT_RGB888 if input_type == "rgb" else image.Format.FMT_BGR888
        )
        print("Generic detector initialized with {} labels".format(len(labels)))
    else:
        detector = nn.YOLO26(MODEL_PATH, dual_buff=False)
        labels = list(detector.labels)
        input_format = detector.input_format()
        print("YOLO26 detector initialized")

    cam = camera.Camera(CAMERA_WIDTH, CAMERA_HEIGHT, input_format)
    disp = display.Display()

    print("Camera detection started")
    print("Press the device exit key to stop")

    while not app.need_exit():
        frame = cam.read()
        if frame is None:
            continue
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

        detection_count = 0
        length = len(results)
        print("当前检测到{}个目标\n".format(length))
        #print("Results: {}".format(results))
        print(f"目标\t置信度\t当前帧率\t")
        for result in results:
            
            class_name, score = draw_detection(frame, result, labels)
            
            if PRINT_DETECTIONS:
                print("{}: {:.2f}".format(class_name, score))
            detection_count += 1
            

            print(f"{result["class_id"]}\t{result["score"]}\t{int(time.fps())}")
        frame.draw_string(
            8,
            8,
            "Objects: {}".format(detection_count),
            color=TEXT_COLOR,
            scale=TEXT_SCALE,
        )
        #print("FPS: {}".format(int(time.fps())))
        disp.show(frame)


if __name__ == "__main__":
    main()
