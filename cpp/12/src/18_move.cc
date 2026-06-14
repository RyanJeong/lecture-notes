#if 0               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
