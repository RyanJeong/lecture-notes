void Snippet1() {
#if 1                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int score = 92;        // Declaring and initializing score
  int& r_score = score;  // Declaring r_score and binding it to score
#endif                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) r_score;
}

void Snippet2() {
#if 1                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int score = 92;        // Declaring and initializing score
  int& r_score = score;  // Declaring r_score and binding it to score
  int num = 80;
  r_score = num;  // now, score becomes 80
#endif            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet3() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int& x = 92;  // Error: cannot bind non-const lvalue reference to an rvalue
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet4() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int temp = 100;
  int& ref1 = temp;       // lvalue reference to temp
  const int& ref2 = 200;  // rvalue reference to a literal
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref1;
  (void) ref2;
}

void Snippet5() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  double* p_pi = &3.141592;  // Error: cannot initialize a pointer with an
                             // literal Literals don't have addresses
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet6() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int num = 100;
  double* p_num = &num;  // Error: cannot convert from int* to double*
                         // In C, this is allowed with a warning
                         // But C++ is a type-safe language; it doesn't allow.
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet7() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int num = 100;
  int* p = &num;    // address-of operator (&)
  int result = *p;  // indirection operator (*)
#endif              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) result;  // Avoid unused variable warning.
  (void) p;       // Avoid unused variable warning.
  (void) num;     // Avoid unused variable warning.
}

void Snippet8() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) x;  // Avoid unused variable warning.
  (void) p;  // Avoid unused variable warning.
}

void Snippet9() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // Void pointer can hold the address of any type
  void* p;  // Declaring a void pointer
  int x = 10;
  p = &x;  // Assigning the address of `x` to the void pointer
  double y = 3.14;
  p = &y;  // Assigning the address of `y` to the void pointer
#endif     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) p;  // Avoid unused variable warning.
  (void) x;  // Avoid unused variable warning.
  (void) y;  // Avoid unused variable warning.
}

void Snippet10() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // If you compile this code with -pedantic-errors option,
  // it will raise an error as follows:
  // error: ISO C++ forbids variable length array 'arr' [-Wvla]
  int size = 10;
  double arr[size];  // The size must be a compile-time constant
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet11() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int* p = new int;  // Dynamically allocate an integer
  p = new int;       // Memory leak! The previous memory is lost
                     // The heap object we allocated previously is still there,
                     // but we have no way to access it anymore
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet12() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int* p = new int;  // Dynamically allocate an integer
  delete p;          // Free the dynamically allocated memory
  delete p;          // UB: double deletion of the same memory
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet13() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int* p = new int;  // Dynamically allocate an integer
  delete p;          // Free the dynamically allocated memory
  *p = 100;          // UB: dangling pointer dereferencing
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet14() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int x = 10;
  delete &x;  // UB: trying to delete a stack object
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
