#ifdef CPP_07_NOBUILD
void SnippetBinaryOp() {
  int i = 10, j = 20;
  j = i;  // now `j` is 10, `j` is lvalue, `i` is rvalue

  int k = i + j;  // 'i' and 'j' are rvalues here

  Fraction fr(1, 2);
  Fraction f2 = fr + 1;  // ok: Fraction + int via implicit conversion
  Fraction f3 = 1 + fr;  // error: int + Fraction; need non-member operator
}
#endif  // CPP_07_NOBUILD
