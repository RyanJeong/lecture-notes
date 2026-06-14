#include "header1.hpp"
#include "header2.hpp"

namespace header1 {
int Func() {
  header2::Bar();  // explicitly from header2
  return Foo();    // from header1
}
}  // namespace header1
