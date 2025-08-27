```cpp
constexpr int x = 5 + 3;  // '5 + 3' is evaluated at compile time, and x becomes
                          // a constant expression.
// The 'constexpr' keyword tells the compiler that the value of 'x' can be
// computed at compile time. This means 'x' will be treated as a constant, and
// no memory will be allocated for it at runtime. Instead, the value '8' will be
// directly embedded in the code wherever 'x' is used.

const int a =
    5 + 3;  // 'a' is a constant, but the value may be computed at runtime
            // (though it's usually optimized by the compiler).
// The 'const' keyword means that 'a' cannot be modified after initialization,
// but it does not guarantee compile-time evaluation. Depending on the context,
// 'a' might occupy memory at runtime, holding the value '8'.

int main() {
  int y = x;  // y is initialized with 8 at runtime, no additional memory used
              // for 'x'
  int z = a;  // z is initialized with 8 at runtime, 'a' may or may not occupy
              // memory depending on compiler optimizations
  return 0;
}
```