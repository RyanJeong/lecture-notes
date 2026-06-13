#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int& Foo() {
  int temp = 10;
  return temp;  // Return by reference, but `temp` is a local variable
                // -> `temp` will be destroyed after the function exits
}

int main() {
  int a = Foo();        // Segmentation fault
  const int b = Foo();  // Segmentation fault
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
