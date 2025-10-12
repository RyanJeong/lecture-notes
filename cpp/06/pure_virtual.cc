class Foo {
 public:
  virtual void
  PureVirtualMethod() = 0;  // Pure virtual function, `= 0`, is a pure virtual
                            // specifier that means "no implementation."
};
