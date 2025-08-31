namespace {
int foo_func() { return 3; }
int foo_var = 1;
}  // anonymous namespace

int main() { foo_var = foo_func(); }
// foo_func, foo_var are not visible outside this file
