#include <iostream>

int main() {
  // Declare a reference to an array. `ref` is now an alias for `arr`.
  int arr[2] = {1, 2};
  int(&ref)[2] = arr;
  std::cout << arr[0] << arr[1]
            << std::endl;  // Outputs the original values: "12"

  // Since `ref` is an alias for `arr`, it changes the values in `arr`.
  ref[0] = ref[1] = 5;
  std::cout << arr[0] << arr[1]
            << std::endl;  // Outputs the modified values: "55"
  return 0;
}
