inline int Add(int a, int b) { return a + b; }

int main() {
  // Function call to 'Add' will be replaced with its body during compilation
  int result = Add(3, 5);
  return result;
}