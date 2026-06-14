#include <deque>  // for std::deque
#include <iostream>

int main() {
  std::deque<char> deq = {'A', 'B', 'C'};

  // Clockwise rotation: A, B, C -> B, C, A
  deq.push_back(deq.front());  // Copy front to back
  deq.pop_front();             // Remove front

  for (char c : deq) std::cout << c << " ";
  std::cout << std::endl;  // B C A
  return 0;
}
