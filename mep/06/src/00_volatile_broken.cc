#include <cstdint>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// UART status register: bit 0 means "transmitter ready".
// DO NOT COPY THIS PATTERN -- the pointer is not volatile.
static std::uint32_t* const kUartStatus =
    reinterpret_cast<std::uint32_t*>(0x10000000);

void WaitForTxReadyBroken() {
  // The compiler may remove or hoist this read because ordinary memory is
  // assumed not to change unless the program writes it.
  while ((*kUartStatus & 0x1u) == 0u) {
    // The source asks for a fresh read, but the pointer is not volatile.
  }
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
