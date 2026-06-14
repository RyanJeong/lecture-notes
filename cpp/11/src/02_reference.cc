int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // lvalue reference
  int x = 10;
  int& ref = x;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) ref;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // rvalue reference
  int&& rref = 20;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) rref;
}