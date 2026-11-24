import json
import matplotlib.pyplot as plt
import numpy as np
import serial

port = "/dev/ttyACM0"
rate = 115200
res = (8, 8)
max_dist = 2000

monitor = serial.Serial(port, rate)

plt.ion() # realtime
image = plt.imshow(np.zeros(res), vmin=0, vmax=max_dist)

while True:
    line = monitor.readline().decode().strip()
    if line.startswith("[") and line.endswith("]"):
        data = json.loads(line)
        image.set_data(np.reshape(data, res))
        plt.pause(0.01)
