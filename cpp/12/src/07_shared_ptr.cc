#include <iostream>
#include <memory>  // for std::shared_ptr

class MyObject {
 public:
  MyObject() { std::cout << "MyObject created" << std::endl; }
  ~MyObject() { std::cout << "MyObject destroyed" << std::endl; }
};

int main() {
  std::shared_ptr<MyObject> ptr1(new MyObject());
  std::cout << "Shared pointers also have get(): " << ptr1.get() << std::endl;
  return 0;
}
