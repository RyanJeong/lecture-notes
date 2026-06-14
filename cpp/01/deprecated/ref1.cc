int main() {
  int a = 10;

  // Reference MUST be initialized at declaration.
  int& ref = a;  // Valid: `ref` is initialized to refer to `a`.
  // int& ref2;  // Error: References must be initialized.

  // Pointer can be declared without initialization.
  int* ptr;  // Valid: `ptr` is declared but not initialized.
  ptr = &a;  // Now `ptr` points to `a`.

  // Pointer can be initialized to nullptr, but reference cannot.
  int* null_ptr = nullptr;  // Valid: `null_ptr` does not point to any object.

  return 0;
}