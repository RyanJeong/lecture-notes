#include "header1.hpp"

namespace header1 {
int func() {
  return foo();  // same as header1::foo()
}
}  // namespace header1
