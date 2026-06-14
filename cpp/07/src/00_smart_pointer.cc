#include <iostream>
#include <string>

class SmartPtr {
 public:
  struct Data {
    int value;
    std::string name;
  };

  explicit SmartPtr(Data* p) : ptr_(p) {}
  ~SmartPtr() { delete ptr_; }

  Data& operator*() const { return *ptr_; }
  Data* operator->() const { return ptr_; }

 private:
  Data* ptr_;
};

int main() {
  SmartPtr sp(new SmartPtr::Data{2, "Alice"});

  // Using member access operator
  std::cout << "sp->value: " << sp->value << std::endl;
  std::cout << "sp->name: " << sp->name << std::endl;

  // Using indirection operator
  std::cout << "(*sp).value: " << (*sp).value << std::endl;
  std::cout << "(*sp).name: " << (*sp).name << std::endl;
  return 0;
}
