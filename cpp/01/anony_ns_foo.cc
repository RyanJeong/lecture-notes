// foo.cc
#include "anony_ns_error.hpp"

namespace {
int Foo() { return 3; }  // definition in another translation unit
}  // namespace
