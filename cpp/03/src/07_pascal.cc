#include <iomanip>
#include <iostream>

int main() {
  int n, max_power = 10;
  do {
    std::cout << "Enter the power of binomial : ";
    std::cin >> n;
  } while (n < 0 || n > max_power);

  int** pascal = new int*[n + 1];
  for (int i = 0; i <= n; ++i) {
    pascal[i] = new int[i + 1];
    for (int j = 0; j <= i; ++j)
      pascal[i][j] = !j || i == j ? 1 : pascal[i - 1][j - 1] + pascal[i - 1][j];
  }

  std::cout << std::endl << "Coefficients for (x + y)^" << n << " are:";
  for (int i = 0; i <= n; ++i) std::cout << std::setw(5) << pascal[n][i];
  std::cout << std::endl;
  for (int i = 0; i <= n; ++i) delete[] pascal[i];
  delete[] pascal;
  return 0;
}
