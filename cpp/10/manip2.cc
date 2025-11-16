#include <iostream>

class Location {
  const char* name_;

 public:
  explicit Location(const char* name) : name_(name) {}

  friend std::ostream& operator<<(std::ostream& stream, const Location& loc) {
    std::cout << '[' << loc.name_ << "] ";
    return stream;
  }
};

void foo() { std::cout << Location(__func__) << "Hello" << std::endl; }
void bar() { std::cout << Location(__func__) << "Hello" << std::endl; }
void qux() { std::cout << Location(__func__) << "Hello" << std::endl; }

int main() {
  foo(), bar(), qux();
  return 0;
}
