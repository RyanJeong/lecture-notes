class B {
 public:
  // Virtual functions' order matters for vtable layout as follows:
  virtual int bar(int x, int y) const { return x + y; }  // vtable[0]
  virtual int qux(int x, int y) const { return x * y; }  // vtable[1]
};

class C : public B {
 public:
  // Class C's vtable layout:
  // vtable[0] -> `C::bar()`
  // vtable[1] -> `B::qux()` (inherited, not overridden)
  int bar(int x, int y) const override { return x - y; }
};
