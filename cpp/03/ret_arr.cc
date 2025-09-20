#include <iostream>

int* CreateArray(const int size) {
  int* arr = new int[size];  // Dynamically allocate an array
  for (int i = 0; i < size; ++i) arr[i] = i * 10;
  // The memory is allocated on the heap, so it will not be destroyed
  // when the function scope ends.
  // But in this case, the caller must remember to free the memory.
  return arr;
}

int main() {
  int size = 5;
  int* my_array = CreateArray(size);
  for (int i = 0; i < size; ++i) std::cout << my_array[i] << " ";
  std::cout << std::endl;
  delete[] my_array;  // Free the dynamically allocated memory
  return 0;
}