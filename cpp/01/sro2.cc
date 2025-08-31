#include "header1.hpp"
#include "header2.hpp"

namespace header1 {
int func() {
  header2::bar();  // explicitly from header2
  return foo();    // from header1
}
}  // namespace header1
