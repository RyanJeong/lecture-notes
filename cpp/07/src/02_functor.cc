#include <iostream>
#include <limits>

class Smallest {
  int value_;

 public:
  Smallest() : value_(std::numeric_limits<int>::max()) {}  // 2^31 - 1

  void operator()(int next) {
    if (next < value_) value_ = next;
  }

  int value() const { return value_; }
};

int main() {
  Smallest smallest;

  smallest(150);  // initialize; value_ updated to 150
  smallest(120);  // side effect: value_ updated to 120
  smallest(140);  // no side effect: value_ remains 120
  smallest(100);  // side effect: value_ updated to 100
  std::cout << "Smallest so far: " << smallest.value() << std::endl;
  return 0;
}
