#include <chrono>  // for measuring execution time
#include <iostream>

int64_t Factorial(int64_t n) { return n == 1 ? 1 : n * Factorial(n - 1); }
// If user calls the function Factorial(5):
// #5 | Factorial(1) |
// #4 | Factorial(2) |
// #3 | Factorial(3) |
// #2 | Factorial(4) |
// #1 | Factorial(5) |
// ---+--------------+
//    |   <STACK>    |

int64_t FactorialTail(int64_t n, int64_t acc = 1) {
  return n == 1 ? acc : FactorialTail(n - 1, acc * n);
}
// If user calls the function FactorialTail(5):
// #1 | FactorialTail(5, 1)   |
// ---+-----------------------+
//    |      <STACK>          |
//              ↓
// #1 | FactorialTail(4, 5)   |
// ---+-----------------------+
//    |      <STACK>          |
//              ↓
//             ...
//              ↓
// #1 | FactorialTail(1, 120) |
// ---+-----------------------+
//    |      <STACK>          |

int64_t memoization[20 + 1] = {0};

int64_t FactorialMemo(int64_t n) {
  if (memoization[n] != 0) return memoization[n];
  memoization[n] = n == 1 ? 1 : n * FactorialMemo(n - 1);
  return memoization[n];
}

int main() {
  // Benchmarking Factorial vs FactorialTail
  {
    auto start = std::chrono::high_resolution_clock::now();
    Factorial(20);  // took about 250 ns
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Factorial execution time: " << duration.count() << " ns"
              << std::endl;  // on my env., it takes about 250 ns
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    FactorialTail(20);  // took about 83 ns
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "FactorialTail execution time: " << duration.count() << " ns"
              << std::endl;  // on my env., it takes about 83 ns
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    FactorialMemo(20);  // took about 209 ns
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "FactorialMemo execution time: " << duration.count() << " ns"
              << std::endl;  // on my env., it takes about 209 ns
  }
  return 0;
}
