#include <functional>  // for std::greater
#include <iostream>
#include <queue>  // for std::priority_queue
#include <vector>

int main() {
  // std::greater<int> means child >= parent
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

  int values[] = {5, 2, 9, 1, 7, 6};
  for (int val : values) min_pq.push(val);

  std::cout << "Added: 5, 2, 9, 1, 7, 6" << std::endl;
  std::cout << "Removal order (smallest first): ";
  while (!min_pq.empty()) {
    std::cout << min_pq.top() << " ";
    min_pq.pop();
  }
  std::cout << std::endl;  // Output: 1 2 5 6 7 9
  return 0;
}
