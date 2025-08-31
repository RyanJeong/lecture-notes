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

void NoRefCase1() {
  // There shall be no references to references, no arrays of references, and no
  // pointers to references.
  int ref[5] = {0, 1, 2, 3, 4};
  (ref + 1);
}

void NoRefCase2() {
  // There shall be no references to references, no arrays of references, and no
  // pointers to references.
  int x = 10;
  int& ref1 = x;
  int& ref2 = ref1;
}