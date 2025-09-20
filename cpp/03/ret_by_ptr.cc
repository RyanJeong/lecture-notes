int* Max(int* x, int* y) { return *x > *y ? x : y; }

int main() {
  int x = 10;
  int y = 20;
  return *Max(&x, &y);
}