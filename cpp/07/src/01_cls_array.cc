#include <cassert>
#include <iostream>

class Array {
 public:
  explicit Array(int s) : size_(s) {
    assert(size_ > 0);
    ptr_ = new double[size_];
  }
  ~Array() { delete[] ptr_; }

  const double& operator[](int index) const {  // Accessor, rvalue
    assert(index >= 0 && index < size_);
    return ptr_[index];
  }

  double& operator[](int index) {  // Mutator, lvalue
    assert(index >= 0 && index < size_);
    return ptr_[index];
  }

 private:
  double* ptr_;
  int size_;
};

int main() {
  Array arr(3);

  // Using mutator to set values
  arr[0] = 22.31;
  arr[1] = 78.61;
  arr[2] = 65.22;

  // Using accessor to get values
  for (int i = 0; i < 3; i++)
    std::cout << "Value of arr [" << i << "]: " << arr[i] << std::endl;
  return 0;
}
