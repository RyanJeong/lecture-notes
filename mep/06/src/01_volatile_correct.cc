#include <cstdint>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Marking the pointee volatile forces a real load on every iteration.
static volatile std::uint32_t* const kUartStatus =
    reinterpret_cast<volatile std::uint32_t*>(0x10000000);

void WaitForTxReady() {
  while ((*kUartStatus & 0x1u) == 0u) {
    // Re-reads the register each time, so hardware updates are observed.
  }
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
