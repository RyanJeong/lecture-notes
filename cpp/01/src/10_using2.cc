#include "header1.hpp"

using namespace header1;  // bring all names from header1
                          // `Foo` and `Bar` are visible as `Foo()` and `Bar()`
int Func() {
  Bar();         // `header1::Bar`
  return Foo();  // `header1::Foo`
}
