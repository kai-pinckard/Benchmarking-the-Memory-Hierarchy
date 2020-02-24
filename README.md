# Kai Pinckard
# Benchmarking-the-Memory-Hierarchy

## Part 1: Benchmarking
Memory_benchmark.cpp measures the latency of reading a byte from memory out of a buffer of N bytes, with N varying from 2^10 to 2^28. For each size, it loops many times to read a byte from a pre-allocated buffer of size n and measures the latency in nanoseconds of this copy. Since the primary goal of this project is to determine the various cache sizes of the computer, it was necessary to access the memory in a very unpredictable way to prevent the prefetcher from prefetching and caching the memory locations of the buffer that would be accessed next. To achieve this, each buffer location was initialized with a random unsigned integer, with each of these random numbers guaranteed to be a valid index into the buffer itself. In this way, the prefetcher was not able to determine which indices would be accessed next, enabling the program to better identify the cache sizes in the system. The following two paragraphs discuss some issues that were overcome in trying to measure the cache performance. The next section contains graphs and the third section contains an analysis of the results.

One difficulty that was overcome in measuring the cache sizes was that memory accesses in the L1 cache are extremely fast, so fast in fact that The C++ functions used to measure the access times take longer than the thing that they are trying to measure. This would lead to extremely inaccurate measurements if it was not dealt with. To solve this issue, many memory accesses were performed during a single measured time interval and then the total measured time was divided by the number of accesses performed to get an estimate of the average access time from the cache.

Another issue that was overcome in attempting to measure the cache sizes and latencies, was that the compiler kept recognizing that the loop that measures the memory access times was not doing anything useful and was optimizing it away. To prevent the compiler from doing this, the variable storing the values read from the buffer was declared volatile. This prevented the compiler from optimizing away the entire loop accessing the memory, which enabled the access times to be measured.

## Part 2: Graphing
![single run graph](https://github.com/kai-pinckard/Benchmarking-the-Memory-Hierarchy/blob/master/single_run_benchmark.png)

This first graph plots the mean memory access latency per memory read in nanoseconds on the Y-axis against the size of the buffer in Kilobytes on the X-axis. Note that this graph was produced by running the memory benchmark once, as a result it is highly influenced by the other operations that happened to be in progress while the benchmark was in progress. Although the trend curve is an interesting addition to the graph that helps show how quickly performance degrades without a prefetcher working properly, it should be noted that the runtime is not expected to neatly fit to a curve, but rather to a step-function, because the cache sizes are discrete.

In an effort to attain more stable results, the graph below was produced, by running the same benchmark with the parameter specifying to run 10 times and plotting the average of the mean memory access latencies per memory read data points instead. Additionally, error bars were included to show how much values were varying between measurements.

![multi run graph](https://github.com/kai-pinckard/Benchmarking-the-Memory-Hierarchy/blob/master/multi_run_benchmark.png)
## Part 3: Analysis

### 1. CPU Cache Sizes:
Based on the graphs above and the raw data, it appears that my cpu has an L2 cache of about 1024kB. Although the access times jumped up significantly for the 1024 kilobyte buffer size, the cache can not be used entirely to store the buffer since cache is likely storing this programs instructions as well as some other things. Additionally, it appears that my cpu has an L1 cache of about 524kB For a similar reason. I think that my CPU has an L3 cache of about 33554kB since the data usually shows a large performace decrease at or just after this buffer size. 

I think that the reason the above graphs are not monotonously increasing is because the operating system and the other programs running on my computer at the same time as the benchmark can slow down its execution. Since there is no guarantee that these other factors will act uniformly across the different buffer size benchmarks, certain benchmarks of a larger size can get lucky in that they were interrupted less than others. This can explain why sometimes a larger buffer size had faster average access times. 

I think that the reason that the graph is not a step function is that the benchmark is likely to have at least a part of the buffer in its cache when it is performing the accesses, allowing it to occasionally get the faster cache hit time than the miss time. Furthermore, the hit rate of the cache does not go down to zero as soon as the buffer is larger than the cache, instead the hit rate is likely inversely proportional to the buffer size. 

### 2. Comparing Performance with Expected Results:
According to Peter Norvig's [page](http://norvig.com/21-days.html#answers), a fetch from the L1 cache takes about a half of a nanosecond. This is between a third and a sixth of the fastest access times measured by my benchmark, suggesting that although the benchmark was careful to measure the access times and little else, the fact that it used a loop likely slowed it down substantially. Since the loop requires accessing the iteration variable, making a comparison, and incrementing the value of the iteration variable, this likely overshadowed the time taken by the memory access that we were trying to measure. In an effort to alleviate this issue, I tried having the benchmark perform multiple accesses per loop iteration, however, it showed no improvement. Another factor that might have caused the benchmark to measure such long L1 and L2 access times is that the operating system is able to interrupt the benchmarks execution and the cpu may be splitting cycles between several processes. L2 cache access times were likely inflated for similar reasons. Norvig does not provide times for the L3 cache access times, but these would probably also be higher than Norvig would report. This is because the benchmark is only able to measure the complete time it takes to read a variable which for L3 includes the time it takes to search L1 the time it takes to search L2 and then the time it takes to find the value in the L3 cache. 

### 3. Actual CPU Caches Sizes with the Predicted Sizes:
Upon opening the cpuinfo file on my computer I found the following.

model name	: Intel(R) Core(TM) i7-4500U CPU @ 1.80GHz
stepping	: 1
microcode	: 0x25
cpu MHz		: 1485.748
cache size	: 4096 KB

Although the file did not say to which cache it refers, I did additional research online and determined that the cache size listed here is an L3 cache that is shared among all the cores. In an attempt to determine the other cache sizes as well I searched the model number and used the time that I got the laptop to make a an informed guess about which the microarchitecture of my process. I think that there is a good chance that my computer is the Sandy Bridge Microcarchitecture, which would mean that it has L1 caches of 64kB per core and L2 Caches of 256Kb per core. Therefore, it appears that my estimates of the cache sizes from 1. were substantially too high. I think that more accurate results could have been achieved if I was able to directly measure only the memory access times. Although the benchmark is careful to measure the read times and little else, it was still necessary to use a loop which involves doing a comparison and accessing the value of the iteration variable. Since including these things in the benchmark times increased the measured times more or less similarly it likely made the L1 and L2 caches appear to have nearly indistinguishable performance.

