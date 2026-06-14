#include <functional>
#include <iostream>

// 1. General function
void GlobalFunc(int x) { std::cout << "Global: " << x << "\n"; }

// 2. Functor
class Functor {
 public:
  void operator()(int x) { std::cout << "Functor: " << x << "\n"; }
};

// 3. Class
class MyClass {
 public:
  void MemberFunc(int x) { std::cout << "Member: " << x << "\n"; }
};

int main() {
  // Declare a std::function that takes an int and returns void
  std::function<void(int)> f;

  // A. Assign a general function
  f = GlobalFunc;
  f(10);  // Output: Global: 10

  // B. Assign a lambda function
  f = [](int x) { std::cout << "Lambda: " << x << "\n"; };
  f(20);  // Output: Lambda: 20

  // C. Assign a functor
  Functor functor;
  f = functor;
  f(30);  // Output: Functor: 30

  // D. Assign a member function (wrapped in a lambda)
  MyClass obj;
  f = [&obj](int x) { obj.MemberFunc(x); };
  f(40);  // Output: Member: 40
  return 0;
}
