#ifdef CPP_06_NOBUILD
void StaticCastDemo() {
  float f = 3.14;      // `f`: 0100 0000 1001 0001 1110 1011 1000 0011
  int implicit_i = f;  // OK, but it's a warning
  int explicit_i = static_cast<int>(f);  // OK, and there's no warning
                                         // `explicit_i`: 0000 ... 0011
  int arr[] = {1, 2, 3};
  float* c_cast_ptr = (float*) arr;  // OK (C-style casting), but it's a warning
  float* cpp_cast_ptr = static_cast<float*>(arr);  // Error, from 'int *' to
                                                   // 'float *' is not allowed
}

void ReinterpretCastDemo() {
  int i = 42;   // `i`:  42, &i: 0x7ffda6a702f8
  int j = 100;  // `j`: 100, &j: 0x7ffda6a702f4
  double* p_double = reinterpret_cast<double*>(&j);
  //     0x7ffda6a702f4        0x7ffda6a702f8
  //     [<--- j(4 bytes) --->][<--- i (4 bytes) --->]
  //     ^
  //     |
  // `p_double` is of type `double*`, so it uses 8 bytes starting from `&j`

  *p_double = 123.456;
  // Now, the value of `i` and `j` are overwritten:
  // `i`: 1079958831
  // `j`:  446676599

  int* p_int = reinterpret_cast<int*>(p_double);  // `p_int` points to `j`
}

void ConstCastDemo(const int& x, const int& y) {
  const int x = 10;
  int y = 20;

  int& x1 = x;        // Error: cannot bind non-const lvalue ref. to const
  const int& x2 = x;  // OK
  int& x3 = const_cast<int&>(x2);  // OK, but be careful!
  x3 = 100;                        // Undefined behavior

  const int& y1 = const_cast<int&>(y);  // OK
  const int& y2 = y;                    // OK
  int& y3 = const_cast<int&>(y2);       // OK
  y3 = 200;                             // OK, `y` is now 200
}
#endif  // CPP_06_NOBUILD
