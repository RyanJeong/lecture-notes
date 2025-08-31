#include "header1.hpp"

using header1::foo;  // only foo is visible as foo()

int func() { return foo(); /* header1::foo */ }
