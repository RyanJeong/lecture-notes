#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <iostream>
#include <memory>  // for std::shared_ptr, std::make_shared,
                   //     std::enable_shared_from_this
class Foo : public std::enable_shared_from_this<Foo> {
  int* data_;

 public:
  Foo() { data_ = new int[100]; }
  ~Foo() { delete[] data_; }

  std::shared_ptr<Foo> GetSharedPtr() { return shared_from_this(); }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
  std::shared_ptr<Foo> pa1 = std::make_shared<Foo>();
  std::shared_ptr<Foo> pa2 = pa1->GetSharedPtr();

  std::cout << "Use count: " << pa1.use_count() << std::endl;
  std::cout << "Use count: " << pa2.use_count() << std::endl;
  return 0;
}
