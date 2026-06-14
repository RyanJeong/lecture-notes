#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// If this function throws an exception even though it is declared noexcept,
// it will invoke a global function std::terminate() and end the program.
void NoExceptFunction() noexcept { throw 1; }

int main() {
  try {
    NoExceptFunction();
  } catch (...) {
    // This block can't catch exceptions from NoExceptFunction
  }
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
