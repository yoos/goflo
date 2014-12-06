import numpy as np
import matplotlib.pyplot as plt

plt.style.use('ggplot')

ys = [[550, 600, 65], [500, 700, 90], [700, 800, 900]]

plt.boxplot(ys, labels=['320x240', '640x480', '1920x1080'])

plt.title("Resolution vs. Processing Time")
plt.ylim((0, 1000))
plt.xlabel("Resolution")
plt.ylabel("Time (ms)")

plt.show()
