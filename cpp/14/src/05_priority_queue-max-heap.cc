#include <functional>  // for std::less
#include <iostream>
#include <queue>  // for std::priority_queue
#include <vector>

int main() {
  // Default is max-heap: std::less<int> means child <= parent
  std::priority_queue<int> max_pq;

  int values[] = {5, 2, 9, 1, 7, 6};
  for (int val : values) max_pq.push(val);

  std::cout << "Added: 5, 2, 9, 1, 7, 6" << std::endl;
  std::cout << "Removal order (largest first): ";
  while (!max_pq.empty()) {
    std::cout << max_pq.top() << " ";
    max_pq.pop();
  }
  std::cout << std::endl;  // Output: 9 7 6 5 2 1
  return 0;
}
