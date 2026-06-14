void Foo1() {
  // If you compile this code with -pedantic-errors option,
  // it will raise an error as follows:
  // error: ISO C++ forbids variable length array 'arr' [-Wvla]
  int size = 10;
  double arr[size];  // The size must be a compile-time constant
  (void) arr;
}
