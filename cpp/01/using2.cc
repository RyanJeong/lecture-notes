#include "header1.hpp"

using namespace header1;  // bring all names from header1
                          // foo and bar are visible as foo() and bar()
int func() {
  bar();         // header1::bar
  return foo();  // header1::foo
}
