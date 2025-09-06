#ifndef CPP_02_CLS_CIRCLE_PROTO_HPP_
#define CPP_02_CLS_CIRCLE_PROTO_HPP_

#ifdef CPP_02_NOBUILD
class Circle {
 public:
  explicit Circle(double radius);  // Parameter Constructor
  Circle();                        // Default Constructor
  Circle(const Circle& circle);    // Copy Constructor
};
#endif  // CPP_02_NOBUILD

#ifdef CPP_02_NOBUILD
class Circle {
 public:
  explicit Circle(double radius)
      : radius_(radius), pi_(3.14) {}  // Initialization list

 private:
  double radius_;
  const double pi_;  // Constant value for Pi
};
#endif  // CPP_02_NOBUILD

#ifdef CPP_02_NOBUILD
class Circle {
 public:
  explicit Circle(double radius);  // Parameter Constructor
  Circle();                        // Default Constructor
  Circle(const Circle& circle);    // Copy Constructor

  ~Circle();  // destructor
};
#endif  // CPP_02_NOBUILD
#endif  // CPP_02_CLS_CIRCLE_PROTO_HPP_