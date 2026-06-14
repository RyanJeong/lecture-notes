#include <iostream>
#include <list>  // for std::list

int main() {
  std::list<int> list1 = {1, 2, 3};
  std::list<int> list2 = {10, 20};

  auto it = list1.begin();
  ++it;  // Points to 2 (no random access, must use ++)

  // Splice: Move all elements of list2 to it position
  // No copying, only pointer rearrangement - O(1)
  list1.splice(it, list2);

  // Result: 1, 10, 20, 2, 3
  // list2 is now empty
  for (int n : list1) std::cout << n << " ";
  std::cout << std::endl;

  return 0;
}
