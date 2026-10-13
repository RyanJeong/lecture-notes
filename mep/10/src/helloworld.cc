#include <cstdio>

// The smallest possible cross-compilation target: no libraries, no GPIO, no
// device access. The only thing under test is the toolchain itself, so when
// something fails you know it is the build and not the hardware.
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int main() {
  std::printf("Hello, World!\n");
  // Proof that the binary really is the target's architecture: an aarch64
  // build reports 8 here even when it was produced on a 32-bit host.
  std::printf("pointer size: %zu bytes\n", sizeof(void*));
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
