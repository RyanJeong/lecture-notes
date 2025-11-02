#include <iostream>

// `n` is a non-type template parameter
template <typename T, int n>
void PrintArray(T (&array)[n]) {
  for (int i = 0; i < n; ++i) std::cout << array[i] << " ";
  std::cout << std::endl;
}

int main() {
  // This template function can automatically determine the size of the array
  // through the non-type template parameter `n` by using array reference
  // syntax.
  int arr1[4] = {7, 3, 5, 1};
  int(&ref1)[4] = arr1;  // `ref1` is a reference to `arr1`
  PrintArray(ref1);

  double arr2[3] = {7.5, 6.1, 4.6};
  PrintArray(arr2);
  return 0;
}
