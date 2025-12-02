int main() {
  // Lambda function definition (type deduction using auto)
  auto add = [](int a, int b) { return a + b; };

  // Lambda function call
  int result = add(3, 5);  // result = 8
  return 0;
}
