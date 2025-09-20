#include <iostream>

int main() {
  int size = 5;
  int* arr = new int[size];  // Array allocation

  // Initialize array
  for (int i = 0; i < size; ++i) arr[i] = i * 10;

  // Print array
  for (int i = 0; i < size; ++i)
    std::cout << "arr[" << i << "] = " << arr[i] << std::endl;

  delete[] arr;  // Array deallocation (note the [])
  return 0;
}