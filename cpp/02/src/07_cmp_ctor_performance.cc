#include <iostream>

class Point {
 public:
  Point(int x, int y) : x_(x), y_(y) {
    std::cout << "Point constructor called" << std::endl;
  }
  Point() : x_(0), y_(0) {
    std::cout << "Point default constructor called" << std::endl;
  }

 private:
  int x_, y_;
};

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Point;
class Student {
 private:
  Point location_;
  int age_;

 public:
  // Efficient: using initialization list (direct initialization)
  Student(const Point& location, int age) : location_(location), age_(age) {}

  // Inefficient: assignment in constructor body (default + assignment)
  Student(int x, int y, int age) {
    location_ = Point(x, y);  // Create default Point, then assign new Point
    age_ = age;               // Assign to undefined value
  }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
