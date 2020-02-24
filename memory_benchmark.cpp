#include <cassert>
#include <chrono>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;
using namespace std::chrono;

/*
This function measures the average amount of time that
it takes to read a byte from an allocated buffer of the
specified size, averaged over the specified number of iters.
*/
double time_buffer_read(unsigned size, unsigned iters)
{
  int* buffer = new int[size];
  // This prevents the compiler from optimizing away the timed loop
  volatile unsigned index = 0;

  // Initialize the buffer with random values
  for (unsigned i = 0; i < size; i++)
  {
    buffer[i] = rand() % size;
  }

  const auto start = steady_clock::now();
  for (unsigned i = 0; i < iters; i++)
  {
    index = buffer[index];
  }
  const auto end = steady_clock::now();

  delete[] buffer;

  auto average_time =  duration_cast<duration<double>>(end - start).count()/iters;
  
  // Convert to nanoseconds
  return average_time * pow(10,9);
}

/*
This benchmark takes one command line argument: The number of times to run the
benchmark. It can be useful to run the benchmark multiple times, because other
processes frequently affect the benchmark's results. The benchmark outputs raw
data into the terminal and also writes the same data to the csv file
"benchmark_caches.csv".
*/
int main(int argc, char** argv)
{
  if (argc != 2)
  {
    cout << "Error please enter exactly one command line argument," << endl;
    cout << "which is the number of times to run the benchmark. " << endl;
    return 1;
  }
  unsigned num_benchmark_runs = strtol(argv[1], nullptr, 10);

  // These two numbers determine which sizes the benchmark will run on. 
  const unsigned exponent_total = 29;
  const unsigned initial_exponent = 10;

  vector<unsigned> sizes;
  vector<double> results;
  unsigned size = 0;
  unsigned iters = 0;
  cout << "|Number of Bytes|Time(Nanoseconds)|" << endl;
  cout << "-----------------------------------" << endl;

  for(unsigned j = 0; j < num_benchmark_runs; j++)
  {
    for(unsigned i = initial_exponent; i < exponent_total; i++)
    {
      iters = pow(2, exponent_total-i);
      size = pow(2,i);

      sizes.push_back(size);
      auto average_time = time_buffer_read(size, iters);
      results.push_back(average_time);
      cout << "       " << size << "       " << average_time << endl;
    }
  }

    ofstream output_file;
    output_file.open("benchmark_caches.csv");
    output_file << "size,average_read_time\n";
    for (unsigned i = 0; i < results.size(); i++)
    {
      output_file << sizes[i] << "," << results[i] << "\n";
    }

    output_file.close();
 
  return 0;
}
