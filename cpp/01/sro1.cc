#include "header1.hpp"

namespace header1 {
int Func() {
  return Foo();  // same as `header1::Foo()`
}
}  // namespace header1
