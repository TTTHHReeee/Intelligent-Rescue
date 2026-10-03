import time
from pathlib import Path

import cv2
import numpy as np
import rclpy
import torch
from cv_bridge import CvBridge
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image
from ultralytics import YOLO


class YoloDepthDemo(Node):
    def __init__(self):
        super().__init__('yolo_depth_demo')

        self.bridge = CvBridge()
        self.window_name = 'YOLO + Depth'
        self.color_frame_count = 0
        self.inference_interval = 5
        self.display_interval = 3
        self.max_depth_delta_ms = 150.0

        self.latest_depth_image = None
        self.latest_depth_stamp = None
        self.first_color_received = False
        self.first_depth_received = False
        self.first_inference_completed = False

        # Create and refresh the window before waiting for ROS images or YOLO.
        cv2.namedWindow(self.window_name, cv2.WINDOW_NORMAL)
        waiting_image = np.zeros((480, 640, 3), dtype=np.uint8)
        cv2.putText(
            waiting_image,
            'Waiting for RGB image...',
            (120, 240),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            (0, 255, 255),
            2,
            cv2.LINE_AA,
        )
        cv2.imshow(self.window_name, waiting_image)
        cv2.waitKey(1)

        model_path = Path(
            '/home/jetson/orbbec_ros2_ws/models/yolo26n.pt'
        )
        if not model_path.is_file():
            raise FileNotFoundError(f'YOLO model not found: {model_path}')

        self.get_logger().info(f'Loading YOLO model: {model_path}')
        self.model = YOLO(str(model_path))

        self.get_logger().info('Fusing YOLO model on CPU...')
        self.model.model.fuse()
        self.get_logger().info('YOLO model fusion completed.')

        if torch.cuda.is_available():
            self.device = 0
            self.use_half = True
            self.get_logger().info(
                f'Using CUDA GPU: {torch.cuda.get_device_name(0)}'
            )
        else:
            self.device = 'cpu'
            self.use_half = False
            self.get_logger().warning('CUDA unavailable; using CPU.')

        # RGB display no longer depends on a message_filters synchronization.
        self.depth_subscription = self.create_subscription(
            Image,
            '/camera/depth/image_raw',
            self.depth_callback,
            qos_profile_sensor_data,
        )
        self.color_subscription = self.create_subscription(
            Image,
            '/camera/color/image_raw',
            self.color_callback,
            qos_profile_sensor_data,
        )

        self.get_logger().info(
            'YOLO depth node started. Press Q or ESC to stop.'
        )

    @staticmethod
    def stamp_to_seconds(stamp):
        return stamp.sec + stamp.nanosec * 1e-9

    @staticmethod
    def get_object_depth(
        depth_image,
        x1,
        y1,
        x2,
        y2,
        shrink_ratio=0.25,
    ):
        image_height, image_width = depth_image.shape

        x1 = max(0, min(int(x1), image_width - 1))
        x2 = max(0, min(int(x2), image_width))
        y1 = max(0, min(int(y1), image_height - 1))
        y2 = max(0, min(int(y2), image_height))

        box_width = x2 - x1
        box_height = y2 - y1
        if box_width <= 0 or box_height <= 0:
            return None, 0, None

        margin_x = int(box_width * shrink_ratio)
        margin_y = int(box_height * shrink_ratio)
        roi_x1 = x1 + margin_x
        roi_x2 = x2 - margin_x
        roi_y1 = y1 + margin_y
        roi_y2 = y2 - margin_y

        if roi_x2 <= roi_x1 or roi_y2 <= roi_y1:
            return None, 0, None

        roi = (roi_x1, roi_y1, roi_x2, roi_y2)
        depth_region = depth_image[roi_y1:roi_y2, roi_x1:roi_x2]
        valid_depths = depth_region[depth_region > 0]

        if valid_depths.size < 20:
            # The center may be a depth hole. Fall back to the full box,
            # while still excluding invalid zero-valued pixels.
            roi = (x1, y1, x2, y2)
            depth_region = depth_image[y1:y2, x1:x2]
            valid_depths = depth_region[depth_region > 0]

        if valid_depths.size < 20:
            return None, valid_depths.size, roi

        return float(np.median(valid_depths)), valid_depths.size, roi

    def depth_callback(self, depth_msg):
        if depth_msg.encoding != '16UC1':
            self.get_logger().warning(
                f'Expected 16UC1 depth, received {depth_msg.encoding}',
                once=True,
            )
            return

        try:
            depth_image = self.bridge.imgmsg_to_cv2(
                depth_msg,
                desired_encoding='passthrough',
            )
        except Exception as error:
            self.get_logger().error(f'Depth conversion failed: {error}')
            return

        self.latest_depth_image = depth_image
        self.latest_depth_stamp = self.stamp_to_seconds(
            depth_msg.header.stamp
        )

        if not self.first_depth_received:
            self.first_depth_received = True
            self.get_logger().info(
                f'First depth frame received: '
                f'{depth_image.shape[1]}x{depth_image.shape[0]}'
            )

    def show_image(self, image):
        cv2.imshow(self.window_name, image)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q') or key == 27:
            if rclpy.ok():
                rclpy.shutdown()

    def color_callback(self, color_msg):
        self.color_frame_count += 1

        try:
            color_image = self.bridge.imgmsg_to_cv2(
                color_msg,
                desired_encoding='bgr8',
            )
        except Exception as error:
            self.get_logger().error(f'Color conversion failed: {error}')
            return

        if not self.first_color_received:
            self.first_color_received = True
            self.get_logger().info(
                f'First color frame received: '
                f'{color_image.shape[1]}x{color_image.shape[0]}'
            )

            # Display RGB before the first CUDA inference starts.
            first_display = color_image.copy()
            cv2.putText(
                first_display,
                'RGB OK - YOLO warming up...',
                (10, 25),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.55,
                (0, 255, 255),
                2,
                cv2.LINE_AA,
            )
            self.show_image(first_display)

        should_infer = (
            self.color_frame_count % self.inference_interval == 0
        )

        if not should_infer:
            # Keep the raw RGB view alive while skipping inference frames.
            if self.color_frame_count % self.display_interval == 0:
                display_image = color_image.copy()
                depth_state = (
                    'Depth OK'
                    if self.latest_depth_image is not None
                    else 'Waiting for depth'
                )
                cv2.putText(
                    display_image,
                    depth_state,
                    (10, 25),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.55,
                    (0, 255, 255),
                    2,
                    cv2.LINE_AA,
                )
                self.show_image(display_image)
            return

        color_time = self.stamp_to_seconds(color_msg.header.stamp)
        depth_image = self.latest_depth_image
        depth_delta_ms = None
        depth_is_usable = False
        depth_problem = 'depth frame unavailable'

        if depth_image is not None and self.latest_depth_stamp is not None:
            depth_delta_ms = abs(
                color_time - self.latest_depth_stamp
            ) * 1000.0
            same_size = (
                color_image.shape[:2] == depth_image.shape[:2]
            )
            depth_is_usable = (
                same_size
                and depth_delta_ms <= self.max_depth_delta_ms
            )
            if not same_size:
                depth_problem = (
                    f'size mismatch: color='
                    f'{color_image.shape[1]}x{color_image.shape[0]}, '
                    f'depth={depth_image.shape[1]}x{depth_image.shape[0]}'
                )
            elif depth_delta_ms > self.max_depth_delta_ms:
                depth_problem = (
                    f'stale depth: delta={depth_delta_ms:.1f} ms'
                )
            else:
                depth_problem = 'none'

        if not self.first_inference_completed:
            self.get_logger().info(
                'Starting first YOLO CUDA inference...'
            )

        inference_start = time.perf_counter()
        try:
            results = self.model.predict(
                source=color_image,
                imgsz=320,
                conf=0.30,
                iou=0.50,
                device=self.device,
                half=self.use_half,
                verbose=False,
            )
        except Exception as error:
            self.get_logger().error(f'YOLO inference failed: {error}')
            return

        inference_ms = (
            time.perf_counter() - inference_start
        ) * 1000.0

        if not self.first_inference_completed:
            self.first_inference_completed = True
            self.get_logger().info(
                f'First YOLO inference completed in '
                f'{inference_ms:.1f} ms.'
            )

        display_image = color_image.copy()
        boxes = results[0].boxes
        detection_messages = []

        if boxes is not None:
            xyxy_values = boxes.xyxy.cpu().numpy()
            confidence_values = boxes.conf.cpu().numpy()
            class_values = boxes.cls.cpu().numpy()

            for xyxy, confidence, class_id in zip(
                xyxy_values,
                confidence_values,
                class_values,
            ):
                x1, y1, x2, y2 = xyxy.astype(int)
                class_name = self.model.names[int(class_id)]

                depth_mm = None
                valid_count = 0
                depth_roi = None
                if depth_is_usable:
                    depth_mm, valid_count, depth_roi = (
                        self.get_object_depth(
                            depth_image,
                            x1,
                            y1,
                            x2,
                            y2,
                        )
                    )

                cv2.rectangle(
                    display_image,
                    (x1, y1),
                    (x2, y2),
                    (0, 255, 0),
                    2,
                )

                if depth_roi is not None:
                    rx1, ry1, rx2, ry2 = depth_roi
                    cv2.rectangle(
                        display_image,
                        (rx1, ry1),
                        (rx2, ry2),
                        (255, 0, 0),
                        1,
                    )

                if depth_mm is not None:
                    label = (
                        f'{class_name} {confidence:.2f} '
                        f'{depth_mm / 1000.0:.2f} m'
                    )
                    detection_messages.append(
                        f'{class_name}: conf={confidence:.2f}, '
                        f'depth={depth_mm:.0f} mm, '
                        f'valid={valid_count}'
                    )
                    label_color = (0, 255, 0)
                elif not depth_is_usable:
                    label = (
                        f'{class_name} {confidence:.2f} '
                        f'NO SYNC DEPTH'
                    )
                    label_color = (0, 165, 255)
                    detection_messages.append(
                        f'{class_name}: conf={confidence:.2f}, '
                        f'NO SYNC DEPTH ({depth_problem})'
                    )
                else:
                    label = f'{class_name} {confidence:.2f} NO DEPTH'
                    label_color = (0, 0, 255)
                    detection_messages.append(
                        f'{class_name}: conf={confidence:.2f}, '
                        f'NO DEPTH, valid_pixels={valid_count}'
                    )

                cv2.putText(
                    display_image,
                    label,
                    (x1, max(y1 - 8, 20)),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.5,
                    label_color,
                    2,
                    cv2.LINE_AA,
                )

        detection_count = len(boxes) if boxes is not None else 0
        depth_text = (
            f'{depth_delta_ms:.1f} ms'
            if depth_delta_ms is not None
            else 'unavailable'
        )
        status_text = (
            f'Infer {inference_ms:.1f} ms | '
            f'Depth delta {depth_text} | '
            f'Objects {detection_count}'
        )
        cv2.putText(
            display_image,
            status_text,
            (10, 25),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.5,
            (0, 255, 255),
            2,
            cv2.LINE_AA,
        )

        if self.color_frame_count % 30 == 0:
            if detection_messages:
                self.get_logger().info(
                    ' | '.join(detection_messages)
                    + f' | inference={inference_ms:.1f} ms'
                    + f' | depth_delta={depth_text}'
                )
            else:
                self.get_logger().info(
                    f'Objects={detection_count}, '
                    f'inference={inference_ms:.1f} ms, '
                    f'depth_delta={depth_text}'
                )

        self.show_image(display_image)

    def destroy_node(self):
        cv2.destroyAllWindows()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = YoloDepthDemo()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
