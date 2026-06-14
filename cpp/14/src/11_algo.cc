#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
bool Descending(int a, int b) { return a > b; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::vector<int> vec1 = {5, 2, 9, 1};
  std::sort(vec1.begin(), vec1.end(), Descending);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  for (const auto& i : vec1) std::cout << i << " ";
  std::cout << std::endl;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::vector<int> vec2 = {5, 2, 9, 1};
  std::sort(vec2.begin(), vec2.end(), std::greater<int>());  // Descending order
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  for (const auto& i : vec2) std::cout << i << " ";
  std::cout << std::endl;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::vector<int> vec3 = {5, 2, 9, 1};
  std::sort(vec3.begin(), vec3.end(), [](int a, int b) { return a > b; });
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  for (const auto& i : vec3) std::cout << i << " ";
  std::cout << std::endl;

  return 0;
}
