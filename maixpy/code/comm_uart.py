
from maix import app, uart, pinmap, time, sys, err
import struct
ports = uart.list_devices()

# get pin and UART number according to device id
device_id = sys.device_id()
if device_id == "maixcam2":
    pin_function = {
        "A21": "UART4_TX",
        "A22": "UART4_RX"
        # "B0": "UART2_TX",
        # "B1": "UART2_RX"
    }
    device = "/dev/ttyS4"
    # device = "/dev/ttyS2"
else:
    pin_function = {
        "A16": "UART0_TX",
        "A17": "UART0_RX"
    }
    device = "/dev/ttyS0"

for pin, func in pin_function.items():
    err.check_raise(pinmap.set_pin_function(pin, func), f"Failed set pin{pin} function to {func}")

# Init UART
serial_dev = uart.UART(device, 115200)


# data = "hello 1\r\n".encode()

# 发送单个原始字节 0x05；串口助手切换到 HEX 显示后应看到 05。
data = struct.pack(">HH", 81, 163)
# serial_dev.write_str(data)
# print("sent:", data)

# data = "object {} at x: {} y: {} w: {} h: {}, prob: {:.2f}\r\n".format("apple", 100, 100, 80, 80, 0.98123)
# serial_dev.write_str(data)
# print("sent:", data)
# serial_dev.write(data)
print("now wait receive data:")
while not app.need_exit():
    serial_dev.write(data)
    print(data)
    # print("sent HEX:", data.hex(" ").upper())

    # data = serial_dev.read()
    # if serial_dev.read():
    #     print("Received, type: {}, len: {}, data: {}".format(type(data), len(data), data))
    #     serial_dev.write(data)

    time.sleep_ms(100) # 每 100 ms 发送一次



