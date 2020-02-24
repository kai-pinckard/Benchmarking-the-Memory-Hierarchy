# Kai Pinckard
# Benchmarking-the-Memory-Hierarchy

## Part 1: Benchmarking
Memory benchmark. CPP measures the latency of reading a bite from memory out of a buffer of and bytes, where n is the number varying from 2 ^ 10 to 2 ^ 28. breech size and it Loops many times to read a bite from a pre allocated buffer of size n and measures the latency in nanoseconds of this copy. Since the primary goal of this project is to determine the various cache sizes of the computer, it was necessary to access the memory in a very unpredictable way to prevent the prefecture from prefetching and caching the memory locations of the buffer that would be accessed next. In order to achieve this the buffer was initialized with a random unsigned integer in every memory location, with each of these random numbers guaranteed To be a valid in to see into the buffer itself. In this way the prefecture was not able to determine which indices would be accessed next until it had already read the value from the memory location effectively preventing prefetching and enabling the program to  better identify the cash sizes in the system. The following two paragraphs discuss some issues that were overcome in trying to measure the cache performance.The next section contains graphs of results and an explanation of the graphs.  The third section contains an analysis of the results.

One difficulty that was overcome in measuring the cache sizes was that memory access is from the L1 cache are extremely fast, so fast in fact that The C plus plus functions used to measure the access times actually take longer than the thing that they are trying to measure. This would lead to extremely inaccurate measurements if it was not dealt with. In order to solve this issue, many memory accesses were performed during a single measured time interval and then the total measured time was divided by the number of accesses performed to get an estimate of the average access time from the cache.

Another issue that was overcome in attempting to measure the cash sizes and latencies, was that since compiler optimization was turned on at the O3 level it was necessary to actually use the values that we're being read from memory for some kind of purpose. This prevented the compiler from optimizing away the entire loop accessing the memory  and thus defeating the purpose of the entire program.

## Part 2: Graphing
![single run graph](https://github.com/kai-pinckard/Benchmarking-the-Memory-Hierarchy/blob/master/single_run_benchmark.png)

This first graph plots the mean memory access latency per memory read in nanoseconds on the Y-axis against the size of the buffer in Kilobytes on the X-axis. Note that this graph was produced by running the memory benchmark once, as a result it is highly influenced by the other operations that happened to be in progress while the benchmark was in progress. Although the trend curve is an interesting addition to the graph that helps show how quickly performance degrades without a prefetcher working properly, it should be noted that the runtime is not expected to neatly fit to a curve, but rather to a step-function, because the cache sizes are discrete.

In an effort to attain more stable results, the graph below was produced, by running the same benchmark with the parameter specifying to run 10 times and plotting the average of the mean memory access latencies per memory read data points instead. 

![multi run graph](https://github.com/kai-pinckard/Benchmarking-the-Memory-Hierarchy/blob/master/multi_run_benchmark.png)
## Part 3: Analysis

### 1. CPU Cache Sizes:

### 2. Comparing Performance with Expected Results:

### 3. Actual CPU Caches Sizes with the Predicted Sizes:
