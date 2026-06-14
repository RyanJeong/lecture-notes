void Snippet1() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction f1(3, 4);
  Fraction f2(1, 2);

  f1.Add(f2);  // Using member function
  f1 + f2;     // Using overloaded + operator
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet2() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction* ptr_fr = new Fraction(3, 4);

  Foo();  // Some errors may occur here, e.g., exceptions thrown, and the object
          // pointed to by `ptr_fr` may not be properly deleted.
  delete ptr_fr;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet3() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int i = 10, j = 20;
  j = i;  // now `j` is 10, `j` is lvalue, `i` is rvalue
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int k = i + j;  // 'i' and 'j' are rvalues here
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction fr(1, 2);
  Fraction f2 = fr + 1;  // ok: Fraction + int via implicit conversion
  Fraction f3 = 1 + fr;  // error: int + Fraction; need non-member operator
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void Foo(int a, int b = 10, int c = 20);  // OK
void Bar(int a, int b = 10, int c);       // Error
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void Qux(int x, int y = 100);
void Qux(int x);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet4() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Qux(1, 2);  // Calls Qux(int x, int y = 100)
  Qux(3);     // Error: Ambiguous call
              // Qux(int x, int y = 100) can also be called with one argument
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}