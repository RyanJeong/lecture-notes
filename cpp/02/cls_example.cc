#include <iostream>

class Circle {
  double radius_;  // Data member (using the default access specifier - private)

 public:  // Member functions
  void set_radius(double radius);
  double get_radius() const;
};  // A semicolon is needed at the end of class definition

double Circle::get_radius() const { return radius_; }
void Circle::set_radius(double r) { radius_ = r; }

int main() {
  Circle circle;
  circle.set_radius(10);
  std::cout << circle.get_radius() << std::endl;
  return 0;
}
