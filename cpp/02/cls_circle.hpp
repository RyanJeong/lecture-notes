#ifndef CPP_02_CLS_CIRCLE_HPP_
#define CPP_02_CLS_CIRCLE_HPP_

// Forward declaration of the Circle class
class Circle;

// Definition of the Circle class
class Circle {
 private:
  // Data members of classes, both static and non-static, are named like
  // ordinary nonmember variables, but with a trailing underscore.
  double radius_;  // data members or variables

 public:
  void set_radius(double radius);  // member functions or methods
};  // A semicolon is needed at the end of class definition

#endif  // CPP_02_CLS_CIRCLE_HPP_
