#include <cstdint>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Memory-mapped GPIO output register on a BCM2835-class SoC.
// Accessing hardware through a non-volatile pointer lets the optimizer treat
// a write that is never read again as a dead store and delete it.
static volatile std::uint32_t* const kGpioSet0 =
    reinterpret_cast<volatile std::uint32_t*>(0x3F20001C);

void SetGpio17High() { *kGpioSet0 = (1u << 17); }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
