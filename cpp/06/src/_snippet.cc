#include <iostream>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Animal {
 public:
  virtual void Move() const { std::cout << "Animal moves" << std::endl; }
};

class Dog : public Animal {
 public:
  virtual void Move(int y, int x) const {  // New virtual function
    // Not an override; different signature
    // If you write 'override' here, it will cause a compilation error.
    std::cout << "Dog moves to (" << y << ", " << x << ")" << std::endl;
  }
  void Move() const override {  // Proper override
    std::cout << "Dog moves" << std::endl;
  }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class B {
 public:
  // Virtual functions' order matters for vtable layout as follows:
  virtual int Bar(int x, int y) const { return x + y; }  // vtable[0]
  virtual int Qux(int x, int y) const { return x * y; }  // vtable[1]
};

class C : public B {
 public:
  // Class C's vtable layout:
  // vtable[0] -> `C::Bar()`
  // vtable[1] -> `B::Qux()` (inherited, not overridden)
  int Bar(int x, int y) const override { return x - y; }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet1(void) {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  float f = 3.14;      // `f`: 0100 0000 1001 0001 1110 1011 1000 0011
  int implicit_i = f;  // OK, but it's a warning
  int explicit_i = static_cast<int>(f);  // OK, and there's no warning
                                         // `explicit_i`: 0000 ... 0011
  int arr[] = {1, 2, 3};
  float* c_cast_ptr = (float*) arr;  // OK (C-style casting), but it's a warning
  float* cpp_cast_ptr = static_cast<float*>(arr);  // Error, from 'int *' to
                                                   // 'float *' is not allowed
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet2(void) {
#if 1           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) p_int;     // Avoid unused variable warning.
  (void) p_double;  // Avoid unused variable warning.
  (void) i;         // Avoid unused variable warning.
  (void) j;         // Avoid unused variable warning.
}

void Snippet3(void) {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
