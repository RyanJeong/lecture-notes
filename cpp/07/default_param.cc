#include <iostream>
#include <string>

void Display(const std::string& msg = "Hello, world!") {
  std::cout << msg << std::endl;
}

int main() {
  Display();              // Uses default parameter
  Display("Hello C++!");  // Overrides default parameter
  return 0;
}

#ifdef CPP_07_NOBUILD
void Foo(int a, int b = 10, int c = 20);  // OK
void Bar(int a, int b = 10, int c);       // Error

void Qux(int x, int y = 100);
void Qux(int x);

void AmbiguityTest() {
  Qux(1, 2);  // Calls Qux(int x, int y = 100)
  Qux(3);     // Error: Ambiguous call
              // Qux(int x, int y = 100) can also be called with one argument
}
#endif
