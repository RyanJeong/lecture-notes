#include <iostream>
#include <memory>  // for std::weak_ptr, std::shared_ptr, std::make_shared

int main() {
  std::weak_ptr<int> weak;

  {
    std::shared_ptr<int> sp = std::make_shared<int>(42);
    weak = sp;  // weak_ptr (`weak`) observes the shared_ptr
    if (std::shared_ptr<int> locked = weak.lock())
      std::cout << "Shared pointer's value: " << *locked << std::endl;
    std::cout << "`locked` goes out of scope here, so the strong count is "
              << sp.use_count() << std::endl;  // strong count is 1
  }

  if (std::shared_ptr<int> locked = weak.lock())
    std::cout << "Shared pointer is still alive: " << *locked << std::endl;
  else
    std::cout << "Shared pointer has been destroyed" << std::endl;
  return 0;
}
