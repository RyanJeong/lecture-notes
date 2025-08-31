#include <cmath>
#include <iostream>

struct Point {
  int x, y;
};

int distance(struct Point* p1, struct Point* p2);

class ClsPoint {
  int x_, y_;

 public:
  int Distance(const ClsPoint& other) const;
};

int main() { return 0; }
