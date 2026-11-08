#include <cstdio>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Add b[i] to a[i] for every element
void AddArrays(int* a, const int* b, int n) {
  for (int i = 0; i < n; ++i) {
    a[i] += b[i];
  }
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
  int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  const int b[8] = {8, 7, 6, 5, 4, 3, 2, 1};
  AddArrays(a, b, 8);
  std::printf("%d\n", a[0]);
  return 0;
}
