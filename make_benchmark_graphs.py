import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns
import os
import time

def single_run_average_latency_graph():
    df = pd.read_csv("benchmark_caches.csv")
    print(df)
    grid = sns.lmplot(x="size", y="average_read_time", data=df, x_bins=19)
    grid.set(xscale="log", ylim=(0, 300))
    grid.set_axis_labels("Size (Bytes)","Average Read Time (Nanoseconds)")
    plt.show()

def multi_run_average_latency_graph():
    df = pd.read_csv("benchmark_caches.csv")
    print(df)
    grid = sns.lmplot(x="size", y="average_read_time", data=df, x_bins=19)
    grid.set(xscale="log", ylim=(0, 300))
    grid.set_axis_labels("Size (Bytes)","Average Read Time (Nanoseconds)")
    plt.show()

if __name__ == "__main__":
    """
    If memory_benchmark was set to run the benchmark multiple times then
    call the multiple_runs_average_latency_graph function, otherwise
    call the single_run_average_latency_graph function
    """
    single_run_average_latency_graph()