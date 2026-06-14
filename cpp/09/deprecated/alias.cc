#include "stack/stack.hpp"

// Note: Template aliases (using) cannot be defined in local (block) scope.
template <typename T>
using Ptr = T*;  // Alias for pointer to `T`

int main() {
  // using new_type_name = existing_type_name;
  using StackInt = Stack<int>;  // Alias for Stack<int>
  StackInt stack(5);

  int x = 42;
  Ptr<int> p = &x;  // Using the `Ptr` alias
  *p = 100;         // Modifying the value pointed to by `p`

  return 0;
}
