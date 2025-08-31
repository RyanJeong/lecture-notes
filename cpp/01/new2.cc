int main() {
  int size = 5;
  int* arr = new int[size];  // Array allocation

  delete[] arr;  // Array deallocation (note the [])
  return 0;
}