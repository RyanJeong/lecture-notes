#include <cstdint>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Read-modify-write: manipulate individual bitfields
static volatile std::uint32_t* const kReg =
    reinterpret_cast<volatile std::uint32_t*>(0x3F200000);

void ModifyBit3() {
  *kReg |= (1u << 3);   // Set bit 3
  *kReg &= ~(1u << 3);  // Clear bit 3
  *kReg ^= (1u << 3);   // Toggle bit 3
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
