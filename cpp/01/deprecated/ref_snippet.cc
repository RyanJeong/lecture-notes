#ifdef CPP_01_NOBUILD
void OptBase() {
  int x = 10;
  int& ref = x;
  ref += 20;
}

void OptStep1() {
  // 1. The compiler converts references and their associated expressions.
  int x = 10;
  int* const ref = &x;
  *ref += 20;
}

void OptStep2() {
  // 2. The compiler optimizes by removing unnecessary memory accesses.
  int x = 10;
  x += 20;
}

void NoRefCases() {
  // There shall be no references to references, no arrays of references, and no
  // pointers to references.

  int a = 1, b = 2, c = 3;
  int& ref_arr[3] = {a, b, c};  // Abandoned: array of references
  // `a`, `b`, and `c` are not guaranteed to be contiguous in memory.
  // What happens if we use the following command?
  (ref_arr + 2);  // Can you sure that (ref_arr + 2) always points to `c`?

  int& ref = a;
  int&* p_ref = &ref;  // Abandoned: pointer to reference
  p_ref = nullptr;     // If this is allowed, `p_ref` can be made invalid.

  // References to references are forbidden in C++ (conflicts with rvalue
  // references). But the following statements are allowed:
  int x = 10;
  int& ref1 = x;
  int& ref2 = ref1;  // `ref2` refers to `x`, not to `ref1`
}
#endif  // CPP_01_NOBUILD
