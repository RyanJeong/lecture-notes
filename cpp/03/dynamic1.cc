#include <iostream>

int main() {
  int size;
  do {
    std::cout << "Enter the array size (larger than zero): ";
    std::cin >> size;
  } while (size <= 0);

  int* p_array = new int[size];
  for (int i = 0; i < size; ++i) p_array[i] = i * 10;
  for (int i = 0; i < size; ++i) std::cout << *(p_array + i) << ' ';
  delete[] p_array;
  return 0;
}
