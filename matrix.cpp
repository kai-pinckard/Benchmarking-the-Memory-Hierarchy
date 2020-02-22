#include <cassert>
#include <chrono>
#include <vector>
#include <random>
#include <iostream>

using namespace std;
using namespace std::chrono;
using dtype = unsigned;

// Increment all elements of mat:
void matrix(unsigned length, unsigned iters)
{
  //allocate space on the heap
  int* mat = new int[length];
  unsigned index = 0;
  cout << RAND_MAX << "--\n";
  //initialize the mat with random values
  for (unsigned i = 0; i < length; i++)
  {
    mat[i] = rand() % length;
  }

  int len = 1000;
  long* fl = new long[len];

  for (unsigned i = 0; i < len; i++)
  {
    fl[i] = rand();
  }

  delete[] fl;

  const auto start = steady_clock::now();
  for (unsigned i = 0; i < iters; i++)
  {
    index = mat[((32*index+27)%length)];
  }
  const auto end = steady_clock::now();
  delete[] mat;
  
  cout << index << std::endl;
  auto average_time =  duration_cast<duration<double>>(end - start).count()/iters;
  cout << "Time to run with matrix: " <<
  average_time << " with size: " << length << std::endl;
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cout << "Error: expected 2 arguments. Received: " << argc-1 << "\n";
    return 1;
  }

  //unsigned MSIZE = strtol(argv[1], nullptr, 0);
  //unsigned times = strtol(argv[2], nullptr, 0);

  for(unsigned i = 10; i < 27; i++)
  {
    matrix(std::pow(2,i), 10);
  }

  return 0;
}

