#include <iostream>

// `n` and `step` are non-type template parameters (`step` has a default value)
template <typename T, int n, int step = 1>
void PrintArray(T (&array)[n]) {
  for (int i = 0; i < n; i += step) std::cout << array[i] << " ";
  std::cout << std::endl;
}

int main() {
  int arr1[4] = {7, 3, 5, 1};
  int(&ref1)[4] = arr1;  // `ref1` is a reference to `arr1`
  PrintArray(ref1);      // `step` uses the default value of 1

  double arr2[6] = {7.5, 6.1, 4.6, 8.2, 9.3, 1.4};
  PrintArray<double, 6, 2>(arr2);  // Using explicit template arguments with
                                   // `step` of 2
  return 0;
}
