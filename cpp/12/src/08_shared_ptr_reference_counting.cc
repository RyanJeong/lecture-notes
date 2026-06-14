#include <iostream>
#include <memory>  // for std::shared_ptr

class MyObject {
 public:
  MyObject() { std::cout << "MyObject created" << std::endl; }
  ~MyObject() { std::cout << "MyObject destroyed" << std::endl; }
};

int main() {
  std::shared_ptr<MyObject> ptr1(new MyObject());
  std::cout << "Strong count (Init): " << ptr1.use_count() << std::endl;
  {  // Copy `ptr1` to `ptr2`, increasing the reference count
    std::shared_ptr<MyObject> ptr2 = ptr1;
    std::cout << "Strong count (Copy): " << ptr2.use_count() << std::endl;
  }  // `ptr2` goes out of scope here, decreasing the reference count
  std::cout << "Strong count (Scope Exit): " << ptr1.use_count() << std::endl;
  return 0;
}
