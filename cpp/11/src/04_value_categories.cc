#include <iostream>
#include <string>

void Lvalue() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int x = 10;
  int& ref = x;                        // `x` is an lvalue
  std::cout << &"Hello" << std::endl;  // "Hello" is an lvalue
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref;
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int GetValue() {
  return 42;  // 42 is a prvalue
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Prvalue() {
#if 1                      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int value = GetValue();  // The expression `GetValue()` is a prvalue.
#endif                     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) value;
}

#include <utility>  // for std::move

void Xvalue1() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::string str = "Hello";

  // std::move returns an xvalue.
  // xvalue is a glvalue, so member functions can be called on it.
  std::move(str).clear();
  std::cout << str << std::endl;  // Outputs an empty string
#endif                            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Xvalue2() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::string str = "Hello";
  // std::move returns an xvalue (std::string&&), which is an rvalue.
  std::string new_str(std::move(str));  // Move constructor invoked
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

class Foo {};

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class WrongMoveConstructor {
  Foo foo_;

 public:
  // Parameter `foo` is of type Foo&& but has a name (`foo`) within this scope.
  // Having a name implies identity, so it is treated as an lvalue.
  explicit WrongMoveConstructor(Foo&& foo)
      : foo_(foo) {}  // Calls Foo's copy constructor
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class CorrectMoveConstructor {
  Foo foo_;

 public:
  // Cast the lvalue `foo` back to an xvalue via std::move to pass it on.
  explicit CorrectMoveConstructor(Foo&& foo)
      : foo_(std::move(foo)) {}  // Calls Foo's move constructor
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
  Lvalue();
  Prvalue();
  Xvalue1();
  return 0;
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void Process(std::string&& s) {
  // If `s` were an rvalue, move constructor would be silently invoked here,
  // causing ambiguity: users wouldn't know if `s` is moved or copied without
  // explicit std::move.
  std::string str = s;
  std::cout << str << std::endl;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
