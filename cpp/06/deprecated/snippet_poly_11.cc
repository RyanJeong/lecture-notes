class B {
 public:
  // Virtual functions' order matters for vtable layout as follows:
  virtual int Bar(int x, int y) const { return x + y; }  // vtable[0]
  virtual int Qux(int x, int y) const { return x * y; }  // vtable[1]
};

class C : public B {
 public:
  // Class C's vtable layout:
  // vtable[0] -> `C::Bar()`
  // vtable[1] -> `B::Qux()` (inherited, not overridden)
  int Bar(int x, int y) const override { return x - y; }
};
