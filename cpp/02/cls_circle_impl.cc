class Circle {
 private:
  double radius_;  // Data member

 public:  // Member functions
  void set_radius(double radius) { radius_ = radius; }
  double get_radius() const { return radius_; }
};  // A semicolon is needed at the end of class definition

#ifdef CPP_02_NOBUILD
class CircleDummy {
 private:
  double radius_;  // Data member

 public:  // Member functions
  inline void set_radius(double radius) { radius_ = radius; }
  inline double get_radius() const { return radius_; }
};  // A semicolon is needed at the end of class definition
#endif
