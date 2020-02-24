import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns

df = pd.read_csv("benchmark_caches.csv")
print(df)
grid = sns.lmplot(x="size", y="average_read_time", data=df, x_bins=19)
grid.set(xscale="log", ylim=(0, 300))
grid.set_axis_labels("Buffer Size(kB)","Mean Latency per Memory Read(ns)")
plt.show()
