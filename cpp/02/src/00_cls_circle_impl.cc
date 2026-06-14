#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Circle {
 private:
  double radius_;  // Data member

 public:  // Member functions
  void set_radius(double radius) { radius_ = radius; }
  double get_radius() const { return radius_; }
};     // A semicolon is needed at the end of class definition
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class CircleDummy {
 private:
  double radius_;  // Data member

 public:  // Member functions
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  inline void set_radius(double radius) { radius_ = radius; }
  inline double get_radius() const { return radius_; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
};  // A semicolon is needed at the end of class definition
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
