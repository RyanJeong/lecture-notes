void Foo1() {
#ifdef CPP_03_NOBUILD
  double* p_pi = &3.141592;  // Error: cannot initialize a pointer with an
                             // literal Literals don't have addresses

#endif  // CPP_03_NOBUILD
}

void Foo2() {
#ifdef CPP_03_NOBUILD
  int num = 100;
  double* p_num = &num;  // Error: cannot convert from int* to double*
                         // In C, this is allowed with a warning
                         // But C++ is a type-safe language; it doesn't allow.

#endif  // CPP_03_NOBUILD
}

void Foo3() {
  int num = 100;
  int* p = &num;    // address-of operator (&)
  int result = *p;  // indirection operator (*)
}

void Foo4() {
  int x = 7;
  int* p = &x;
  if (p) {
    // The pointer `p` is valid (not null)
    // So, the expression p evaluates to true
  }
  p = nullptr;  // Now, `p` is a null pointer
  if (!p) {
    // The pointer `p` is invalid (`p` is null)
    // So, the expression !p evaluates to true
  }
}

void Foo5() {
  // Void pointer can hold the address of any type
  void* p;  // Declaring a void pointer
  int x = 10;
  p = &x;  // Assigning the address of `x` to the void pointer
  double y = 3.14;
  p = &y;  // Assigning the address of `y` to the void pointer
}