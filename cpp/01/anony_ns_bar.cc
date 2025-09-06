// bar.cc
#include "anony_ns_error.hpp"

int Bar() { return Foo(); }  // Tries to call Foo() from bar.cc's namespace
