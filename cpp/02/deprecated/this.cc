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

  double get_radius() const;
#ifdef CPP_02_NOBUILD
  double get_radius(Circle* this) const;
#endif  // CPP_02_NOBUILD

 private:
  double radius_;
  const double pi_;  // Constant value for Pi
};

double Circle::get_radius() const { return radius_; }

void foo() {
  Circle circle;
  circle.get_radius();
}
#ifdef CPP_02_NOBUILD
// `Circle::get_radius()` will be changed by the compiler as below:
double Circle::get_radius(Circle* this) const { return this->radius_; }

void foo() {
  Circle circle;
  Circle* this = &circle;
  circle.get_radius(this);
}
// The caller part will be changed like below:
// Circle* this = &circle1;
// circle1.get_radius(this);
#endif  // CPP_02_NOBUILD

int main() {
  Circle c1;       // Calls default constructor
  Circle c2(5.0);  // Calls parameterized constructor
  Circle c3(c2);   // Calls copy constructor
  return 0;
}
