import numpy as np
import matplotlib.pyplot as plt

plt.style.use('ggplot')

ys = [[550, 600, 65], [500, 700, 90], [700, 800, 900]]

plt.boxplot(ys, labels=['9', '13', '17'])

plt.title("Block Size vs. Processing Time")
plt.ylim((0, 1000))
plt.xlabel("Block Size")
plt.ylabel("Time (ms)")

fig = plt.gcf()
fig.set_size_inches(8, 6)
fig.savefig('block_size.png', dpi=100)
