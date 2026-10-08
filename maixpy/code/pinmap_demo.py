from maix import app, pinmap, uart, time



pinmap.set_pin_function("B0", "UART2_TX")
pinmap.set_pin_function("B1", "UART2_RX")
# funcs = pinmap.get_pin_functions("B0")
# print(funcs)
device = "/dev/ttyS2"
serial_dev = uart.UART(device, 115200)

while not app.need_exit():

        serial_dev.write_str("11")
        print("write success")
        time.sleep_ms(100)
