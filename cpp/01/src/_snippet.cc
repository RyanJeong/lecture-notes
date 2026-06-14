void OptBase() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int x = 10;
  int& ref = x;
  ref += 20;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref; /* Avoid unused variable warning. */
}

void OptStep1() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // 1. The compiler converts references and their associated expressions.
  int x = 10;
  int* const ref = &x;
  *ref += 20;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref; /* Avoid unused variable warning. */
}

void OptStep2() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // 2. The compiler optimizes by removing unnecessary memory accesses.
  int x = 10;
  x += 20;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) x; /* Avoid unused variable warning. */
}

void Snippet1(void) {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int a = 10;

  // Reference MUST be initialized at declaration.
  int& ref = a;  // Valid: `ref` is initialized to refer to `a`.
#if 0            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int& ref2;     // Error: References must be initialized.
#endif           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Pointer can be declared without initialization.
  int* ptr;  // Valid: `ptr` is declared but not initialized.
  ptr = &a;  // Now `ptr` points to `a`.

  // Pointer can be initialized to nullptr, but reference cannot.
  int* null_ptr = nullptr;  // Valid: `null_ptr` does not point to any object.
#endif                      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref;       // Avoid unused variable warning.
  (void) ptr;       // Avoid unused variable warning.
  (void) null_ptr;  // Avoid unused variable warning.
}

#include <iostream>

void Snippet2(void) {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int a = 10;
  int b = 20;

  // `ref` is a reference to `a`.
  int& ref = a;

  // Attempting to change the reference to another variable will modify the
  // original variable instead.
  ref = b;  // This does not change `ref` to refer to `b`, it changes the value
            // of `a` to 20.

  std::cout << "a = " << a << std::endl;      // Output: "a = 20"
  std::cout << "ref = " << ref << std::endl;  // Output: "ref = 20"
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref;  // Avoid unused variable warning.
  (void) a;    // Avoid unused variable warning.
  (void) b;    // Avoid unused variable warning.
}

void Snippet3(void) {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int a = 10;
  int& ref = a;  // `ref` is a reference to `a`.

  // The address of `a` and `ref` are the same
  std::cout << "Address of a: " << &a << std::endl;
  std::cout << "Address of ref: " << &ref
            << std::endl;  // Outputs the same address as `a`.

  // Example where the reference might not have a distinct address:
  int* ptr = &a;     // Pointer to `a`.
  int& ref2 = *ptr;  // Reference to `a` through pointer `ptr`.

  std::cout << "Address of ptr: " << ptr << std::endl;
  std::cout << "Address of ref2: " << &ref2
            << std::endl;  // Same as `a` and `ptr`.
#endif                     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref;   // Avoid unused variable warning.
  (void) ref2;  // Avoid unused variable warning.
  (void) ptr;   // Avoid unused variable warning.
  (void) a;     // Avoid unused variable warning.
}

void NoRefCases() {
  // There shall be no references to references, no arrays of references, and no
  // pointers to references.

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int a = 1, b = 2, c = 3;
  int& ref_arr[3] = {a, b, c};  // Abandoned: array of references
  // `a`, `b`, and `c` are not guaranteed to be contiguous in memory.
  // What happens if we use the following command?
  (ref_arr + 2);  // Can you be sure that (ref_arr + 2) always points to `c`?
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int& ref = a;
  int&* p_ref = &ref;  // Abandoned: pointer to reference
  p_ref = nullptr;     // If this is allowed, `p_ref` can be made invalid.
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // References to references are forbidden in C++ (conflicts with rvalue
  // references). But the following statements are allowed:
  int x = 10;
  int& ref1 = x;
  int& ref2 = ref1;  // `ref2` refers to `x`, not to `ref1`
#endif               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref2; /* Avoid unused variable warning. */
}

// ResolveDangling1()
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int& Max(int& a, int& b) { return (a > b) ? a : b; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

// ResolveDangling2()
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int& Counter() {
  static int counter = 0;  // Static object
  return counter;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
