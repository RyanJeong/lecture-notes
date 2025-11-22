#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

class LargeBuffer {
 public:
  int* data_;

 public:
  explicit LargeBuffer(size_t size = 100'000) { data_ = new int[size]; }

  ~LargeBuffer() {
    if (data_) delete[] data_;
  }

  // Copy constructor (will be called when move is noexcept)
  LargeBuffer(const LargeBuffer& other) : data_(new int[1]) {
    std::cout << "[Copy Constructor] Called\n";
  }

  LargeBuffer(LargeBuffer&& other) noexcept : data_(other.data_) {
    other.data_ = nullptr;
    std::cout << "[Move Constructor - NOEXCEPT] Called\n";
  }

 private:
  LargeBuffer& operator=(const LargeBuffer&) = delete;
  LargeBuffer& operator=(LargeBuffer&&) = delete;
};

class LargeBufferWithoutNoexcept {
 public:
  int* data_;

 public:
  explicit LargeBufferWithoutNoexcept(size_t size = 100'000) {
    data_ = new int[size];
  }

  ~LargeBufferWithoutNoexcept() {
    if (data_) delete[] data_;
  }

  // Copy constructor (will be called when move lacks noexcept)
  LargeBufferWithoutNoexcept(const LargeBufferWithoutNoexcept& other)
      : data_(new int[1]) {
    std::cout << "[Copy Constructor] Called\n";
  }

  // Move constructor WITHOUT noexcept (std::vector prefers copy)
  LargeBufferWithoutNoexcept(LargeBufferWithoutNoexcept&& other)
      : data_(other.data_) {
    other.data_ = nullptr;
    std::cout << "[Move Constructor - NO NOEXCEPT] Called\n";
  }

 private:
  LargeBufferWithoutNoexcept& operator=(
      const LargeBufferWithoutNoexcept&) = delete;
  LargeBufferWithoutNoexcept& operator=(LargeBufferWithoutNoexcept&&) = delete;
};

int main() {
  std::cout << "=== Test 1: With noexcept ===\n";
  std::cout << "std::vector will use move constructor\n";
  std::cout << "Watch the output during reallocation\n\n";
  {
    std::vector<LargeBuffer> vec;

    std::chrono::high_resolution_clock::time_point start =
        std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 20; ++i) {
      vec.push_back(LargeBuffer(100'000));
    }

    std::chrono::high_resolution_clock::time_point end =
        std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> diff = end - start;
    std::cout << "\nElapsed: " << diff.count() << " ms\n\n";
  }

  std::cout << "=== Test 2: Without noexcept ===\n";
  std::cout << "std::vector will use COPY constructor\n";
  std::cout << "Watch the output during reallocation\n\n";
  {
    std::vector<LargeBufferWithoutNoexcept> vec;

    std::chrono::high_resolution_clock::time_point start =
        std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 20; ++i) {
      vec.push_back(LargeBufferWithoutNoexcept(100'000));
    }

    std::chrono::high_resolution_clock::time_point end =
        std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> diff = end - start;
    std::cout << "\nElapsed: " << diff.count() << " ms\n";
  }

  return 0;
}
