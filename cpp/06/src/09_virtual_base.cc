#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Base {
 protected:
  int value = 0;

 public:
  virtual void FuncBase() { ; /* Implement something... */ }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Derived1 : virtual public Base {
 public:
  void FuncBase() override { ; /* Implement something... */ }
  virtual void FuncDerived1() { ; /* Implement something... */ }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Derived2 : virtual public Base {
 public:
  virtual void FuncDerived2() { ; /* Implement something... */ }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class MostDerived : public Derived1, public Derived2 {
 public:
  void FuncBase() override { ; /* Implement something... */ }
  void FuncDerived1() override { ; /* Implement something... */ }
  virtual void FuncMostDerived() { ; /* Implement something... */ }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Test() {
  MostDerived obj_most_derived;  // obj_most_derived at 0x1300

  Base* p_base = &obj_most_derived;
  p_base->FuncBase();
  // p_base=0x1308(Base), vptr[0x1308]->0x2000, vtable[0x2000]->0x3400

  Derived1* p_derived1 = &obj_most_derived;
  p_derived1->FuncBase();
  // p_derived1=0x1300, vptr[0x1300]->0x2500, vtable[0x2500]->0x3400

  p_derived1->FuncDerived1();
  // p_derived1=0x1300, vptr[0x1300]->0x2500, vtable[0x2502]->0x3500

  Derived2* p_derived2 = &obj_most_derived;
  p_derived2->FuncBase();
  // p_derived2=0x1304, vptr[0x1304]->0x2600, vtable[0x2600]->0x3700(thunk)
  // thunk: this-=4(0x1300), call 0x3400

  p_derived2->FuncDerived2();
  // p_derived2=0x1304, vptr[0x1304]->0x2600, vtable[0x2602]->0x3300

  MostDerived* p_most_derived = &obj_most_derived;
  p_most_derived->FuncBase();
  // p_most_derived=0x1300, vptr[0x1300]->0x2500, vtable[0x2500]->0x3400

  p_most_derived->FuncDerived1();
  // p_most_derived=0x1300, vptr[0x1300]->0x2500, vtable[0x2502]->0x3500

  p_most_derived->FuncDerived2();
  // p_most_derived=0x1300, this+=4(0x1304), vptr[0x1304]->0x2600,
  // vtable[0x2602]->0x3300

  p_most_derived->FuncMostDerived();
  // p_most_derived=0x1300, vptr[0x1300]->0x2500, vtable[0x2504]->0x3600
}

void TestValid() {
#if 1                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  MostDerived most_derived;  // most_derived at 0x1300

  Base* p_base = &most_derived;  // point to `Base` subobject
  p_base->FuncBase();
  // p_base=0x1308(Base), vptr[0x1308]->0x2000, vtable[0x2000]->0x3000

  Derived1* p_derived1 = &most_derived;  // point to `Derived1` subobject
  // `Derived1` subobject is at the base address of `MostDerived`; primary vptr
  p_derived1->FuncBase();
  // p_derived1=0x1300, vptr[0x1300]->0x2500, vtable[0x2500]->0x3400

  Derived2* p_derived2 = &most_derived;  // point to `Derived2` subobject
  p_derived2->FuncBase();
  // p_derived2=0x1304, vptr[0x1304]->0x2600, vtable[0x2600]->0x3700(thunk)
  // thunk: 1. [sub this, 4]: adjust `this` (`Derived2` subobject pointer) to
  //           `MostDerived` object base address (0x1300)
  //        2. [jmp 0x3400]: call MostDerived::FuncBase with adjusted `this`

  MostDerived* p_most_derived = &most_derived;  // point to `MostDerived` object
  p_most_derived->FuncMostDerived();
  // p_most_derived=0x1300, vptr[0x1300]->0x2500, vtable[0x2504]->0x3600
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
