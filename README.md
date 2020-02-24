# Kai Pinckard
# Benchmarking-the-Memory-Hierarchy

## Part 1: Benchmarking
Memory_benchmark.cpp measures the latency of reading a byte from memory out of a buffer of N bytes, with N varying from 2^10 to 2^28. For each size, it loops many times to read a byte from a pre-allocated buffer of size n and measures the latency in nanoseconds of this copy. Since the primary goal of this project is to determine the various cache sizes of the computer, it was necessary to access the memory in a very unpredictable way to prevent the prefetcher from prefetching and caching the memory locations of the buffer that would be accessed next. To achieve this, each buffer location was initialized with a random unsigned integer, with each of these random numbers guaranteed To be a valid index into the buffer itself. In this way, the prefetcher was not able to determine which indices would be accessed next, enabling the program to better identify the cache sizes in the system. The following two paragraphs discuss some issues that were overcome in trying to measure the cache performance. The next section contains graphs and the third section contains an analysis of the results.

One difficulty that was overcome in measuring the cache sizes was that memory accesses in the L1 cache are extremely fast, so fast in fact that The C++ functions used to measure the access times take longer than the thing that they are trying to measure. This would lead to extremely inaccurate measurements if it was not dealt with. To solve this issue, many memory accesses were performed during a single measured time interval and then the total measured time was divided by the number of accesses performed to get an estimate of the average access time from the cache.

Another issue that was overcome in attempting to measure the cache sizes and latencies, was that since compiler optimization was turned on at the O3 level the compiler kept recognizing that the loop that measures the memory access times was not doing anything useful and was optimizing it away. To prevent the compiler from doing this, the variable storing the values read from the buffer was declared volatile, making the compiler extremely cautious about optimizing its usage. This prevented the compiler from optimizing away the entire loop accessing the memory, which enabled the access times to be measured.

## Part 2: Graphing
![single run graph](https://github.com/kai-pinckard/Benchmarking-the-Memory-Hierarchy/blob/master/single_run_benchmark.png)

This first graph plots the mean memory access latency per memory read in nanoseconds on the Y-axis against the size of the buffer in Kilobytes on the X-axis. Note that this graph was produced by running the memory benchmark once, as a result it is highly influenced by the other operations that happened to be in progress while the benchmark was in progress. Although the trend curve is an interesting addition to the graph that helps show how quickly performance degrades without a prefetcher working properly, it should be noted that the runtime is not expected to neatly fit to a curve, but rather to a step-function, because the cache sizes are discrete.

In an effort to attain more stable results, the graph below was produced, by running the same benchmark with the parameter specifying to run 10 times and plotting the average of the mean memory access latencies per memory read data points instead. 

![multi run graph](https://github.com/kai-pinckard/Benchmarking-the-Memory-Hierarchy/blob/master/multi_run_benchmark.png)
## Part 3: Analysis

### 1. CPU Cache Sizes:

### 2. Comparing Performance with Expected Results:

### 3. Actual CPU Caches Sizes with the Predicted Sizes:
