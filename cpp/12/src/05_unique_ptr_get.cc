#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <iostream>
#include <memory>  // for smart pointers

class MyObject {
 public:
  void DoSomething() { std::cout << "Doing something\n"; }
};

void UseRawPointer(MyObject* obj) {
  if (obj) obj->DoSomething();
}

int main() {
  std::unique_ptr<MyObject> ptr(new MyObject());
  UseRawPointer(ptr.get());
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void BadPracticeOfGetMethod() {
  std::unique_ptr<MyObject> ptr(new MyObject());
  MyObject* raw_ptr = ptr.get();  // Improperly manage memory using the raw ptr
  delete raw_ptr;  // Logical Error: Deletes the object managed by unique_ptr

  // At the end of scope, unique_ptr will try to delete the object again.
  // -> This leads to undefined behavior (double deletion)
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
