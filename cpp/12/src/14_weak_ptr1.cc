#include <iostream>
#include <memory>  // for std::weak_ptr, std::shared_ptr, std::make_shared

int main() {
  std::weak_ptr<int> weak;
  std::shared_ptr<int> sp = std::make_shared<int>(42);
  std::cout << "Strong count: " << sp.use_count() << std::endl;

  weak = sp;  // weak_ptr (`weak`) observes the shared_ptr
  std::shared_ptr<int> locked = weak.lock();
  if (locked) {
    std::cout << "Shared pointer's value: " << *locked << std::endl;
    std::cout << "Strong count after lock: " << sp.use_count() << std::endl;
  }
  return 0;
}
