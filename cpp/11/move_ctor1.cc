#include <algorithm>  // for std::copy
#include <chrono>     // for timing
#include <iostream>

class LargeData {
  int* data_;

 public:
  LargeData() : data_(new int[1'000'000'000]) {}
  ~LargeData() {
    if (data_) delete[] data_;
  }

  LargeData(const LargeData& other) : data_(new int[1'000'000'000]) {
    std::copy(other.data_, other.data_ + 1'000'000'000, data_);
    std::cout << "Copy constructor called" << std::endl;
  }
};

int main() {
  LargeData a;

  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();

  LargeData b = a;  // This will invoke the copy constructor

  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Copy constructor takes : " << duration.count() << " ms"
            << std::endl;  // 720.672 ms on my machine
  return 0;
}
