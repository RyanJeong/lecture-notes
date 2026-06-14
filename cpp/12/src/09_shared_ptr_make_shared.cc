#if 1              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <memory>  // for std::shared_ptr

class Foo {
  int* data_;

 public:
  Foo() { data_ = new int[100]; }
  ~Foo() { delete[] data_; }
};

int main() {
  Foo* a = new Foo();          // Avoid: Use make_shared instead
  std::shared_ptr<Foo> p1(a);  // Control Block for `p1`, count: 1
  std::shared_ptr<Foo> p2(a);  // Control Block for `p2`, count: 1 -> Not shared
  // CRITICAL: Independent ownership leads to Double Free (Undefined Behavior).
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void SharedPtrMakeSharedExample() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  {
    // Traditional way to create a shared_ptr
    std::shared_ptr<Foo> ptr1(new Foo());
    std::shared_ptr<Foo> ptr2 = ptr1;  // Shared pointers can be copied
  }
  {
    // You can replace std::shared_ptr<Foo> ptr(new Foo()) with:
    std::shared_ptr<Foo> ptr1 = std::make_shared<Foo>();
    std::shared_ptr<Foo> ptr2 = ptr1;
  }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
