#include <iostream>
#include <vector>

class MyClass {
 public:
  int id_;

  explicit MyClass(int id) : id_(id) {
    std::cout << "Ctor: " << id_ << std::endl;
  }
  MyClass(const MyClass& other) : id_(other.id_) {
    std::cout << "Copy Ctor: " << id_ << std::endl;
  }
};

int main() {
  std::vector<MyClass> vec;
  vec.emplace_back(101);  // Direct construction (no copy!)
  return 0;
}
