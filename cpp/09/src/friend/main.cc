#include <iostream>

#include "friend.hpp"

int main() {
  std::cout << "Demonstrating friend functions with class templates:\n";
  FreeFunction();
  TemplateFunction(5);
  TemplateFunction(3.14);

  std::cout << "All friend function demonstrations completed.\n";
  return 0;
}