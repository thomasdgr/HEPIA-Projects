# coding: utf-8

"""
pad = Gamepad()
pad.start()
while True:
    for i in range(10):
        pad.x_val = i * 10
        time.sleep(1)
"""

import threading
import time
import uinput


class Gamepad:
    def __init__(
        self, x_min: int = -100, x_max: int = 100, y_min: int = -100, y_max: int = 100
    ):
        self.events = (
            uinput.ABS_X + (x_min, x_max, 0, 0),
            uinput.ABS_Y + (y_min, y_max, 0, 0),
        )
        self.x_min = x_min
        self.x_max = x_max
        self.y_min = y_min
        self.y_max = y_max
        self.x_val = 0
        self.y_val = 0

    def pt(self):
        with uinput.Device(self.events) as device:
            while True:
                device.emit(uinput.ABS_X, self.x_val)
                device.emit(uinput.ABS_Y, self.y_val)
                time.sleep(0.1)

    def start(self):
        threading.Thread(target=self.pt).start()
