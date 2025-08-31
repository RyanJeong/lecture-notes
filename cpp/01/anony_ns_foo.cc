// foo.cc
#include "anony_ns_error.hpp"

namespace {
int foo_func() { return 3; }  // definition in another translation unit
}  // namespace
