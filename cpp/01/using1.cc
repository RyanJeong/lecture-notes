#include "header1.hpp"

using header1::Foo;  // only `Foo` is visible as `Foo()`

int func() { return Foo(); /* header1::Foo */ }
