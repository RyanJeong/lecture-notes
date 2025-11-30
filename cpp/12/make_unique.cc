#include <iostream>
#include <memory>  // fot std::unique_ptr, std::make_unique

class MyObject {
 public:
  void DoSomething() { std::cout << "Doing something\n"; }
};

int main() {
  {
    // Traditional way to create a unique_ptr
    std::unique_ptr<MyObject> ptr(new MyObject());
    ptr->DoSomething();
  }
  {
    // You can replace std::unique_ptr<MyObject> ptr(new MyObject()) with:
    std::unique_ptr<MyObject> ptr = std::make_unique<MyObject>();
    ptr->DoSomething();
  }
  return 0;
}
