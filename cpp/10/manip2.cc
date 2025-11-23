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

void Foo() { std::cout << Location(__func__) << "Hello" << std::endl; }
void Bar() { std::cout << Location(__func__) << "Hello" << std::endl; }
void Qux() { std::cout << Location(__func__) << "Hello" << std::endl; }

int main() {
  Foo(), Bar(), Qux();
  return 0;
}
