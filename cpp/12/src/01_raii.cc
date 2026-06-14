#include <iostream>

class Resource {
 public:
  Resource() { std::cout << "Acquired resource\n"; }
  ~Resource() { std::cout << "Released resource\n"; }
};

int main() {
  {
    Resource res;  // Acquire resource upon construction
    // Use the resource
  }  // Automatically release resource upon scope exit
  return 0;
}