#include <algorithm>  // for std::copy
#include <chrono>     // for timing
#include <iostream>
#include <utility>  // for std::move

class LargeData {
  int* data_;

 public:
  LargeData() : data_(new int[1'000'000'000]) {}
  ~LargeData() {
    if (data_) delete[] data_;
  }

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  LargeData(LargeData&& other) noexcept : data_(other.data_) {
    other.data_ = nullptr;  // IMPORTANT: Nullify the source's data pointer
    std::cout << "Move constructor called" << std::endl;
  }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
};

int main() {
  LargeData a;

  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();

#if 1                          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  LargeData b = std::move(a);  // This will invoke the move constructor
#endif                         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Move constructor takes : " << duration.count() << " ms"
            << std::endl;  // 0.059458 ms on my machine
  return 0;
}
