namespace {
int Foo() { return 3; }
int foo_var = 1;
}  // anonymous namespace

int main() { foo_var = Foo(); }
// `Foo`, `foo_var` are not visible outside this file
