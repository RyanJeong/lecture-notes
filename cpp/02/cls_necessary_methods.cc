#include <iostream>

class Circle {
 public:
  explicit Circle(double radius) : radius_(radius), pi_(3.14) {
    std::cout << "Parameterized ctor: " << radius_ << std::endl;
  }
  Circle() : radius_(1.0), pi_(3.14) {
    std::cout << "Default ctor: " << radius_ << std::endl;
  }
  Circle(const Circle& circle) : radius_(circle.radius_), pi_(circle.pi_) {
    std::cout << "Copy ctor: " << radius_ << std::endl;
  }

  ~Circle() { std::cout << "Dtor: " << radius_ << std::endl; }

 private:
  double radius_;
  const double pi_;  // Constant value for Pi
};

int main() {
  Circle c1;       // Calls default constructor
  Circle c2(5.0);  // Calls parameterized constructor
  Circle c3(c2);   // Calls copy constructor
  return 0;
}
