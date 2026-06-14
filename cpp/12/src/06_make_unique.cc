#include <iostream>
#include <memory>  // fot std::unique_ptr, std::make_unique

class MyObject {
 public:
  void DoSomething() { std::cout << "Doing something\n"; }
};

void UniquePtrs(std::unique_ptr<MyObject> p1, std::unique_ptr<MyObject> p2) {
  p1->DoSomething();
  p2->DoSomething();
}

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
  // An exception may occur, which may cause a memory leak. (not exception-safe)
  UniquePtrs(std::unique_ptr<MyObject>(new MyObject()),
             std::unique_ptr<MyObject>(new MyObject()));
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  return 0;
}
