#include <iostream>

void PassArrViaPtr(const int* p, int size) {
  for (int i = 0; i < size; ++i) std::cout << *(p++) << " ";
  std::cout << std::endl;
}

void PassArrViaArr(const int arr[], int size) {
  for (int i = 0; i < size; ++i) std::cout << arr[i] << " ";
  std::cout << std::endl;
}

int main() {
  int array[] = {2, 3, 5, 7, 11, 13};
  int size = sizeof(array) / sizeof(array[0]);
  PassArrViaPtr(array, size);
  PassArrViaArr(array, size);
  return 0;
}
