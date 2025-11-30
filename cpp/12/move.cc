#ifdef CPP_12_NOBUILD
#include <memory>   // for std::unique_ptr, std::make_unique
#include <utility>  // for std::move

class Resource;  // Forward declaration

void ProcessResource(std::unique_ptr<Resource> res) {
  // Use `res` at here
}

int main() {
  std::unique_ptr<Resource> my_resource = std::make_unique<Resource>();

  // Transfer ownership using move semantics
  ProcessResource(std::move(my_resource));
  // `my_resource` is now nullptr
  return 0;
}
#else
int main() { return 0; }
#endif  // CPP_12_NOBUILD
