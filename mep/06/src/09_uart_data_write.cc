#include <cstdint>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// UART data register: every write transmits one character.
static std::uint32_t* const kUartDataBroken =
    reinterpret_cast<std::uint32_t*>(0x10000004);
static volatile std::uint32_t* const kUartData =
    reinterpret_cast<volatile std::uint32_t*>(0x10000004);

void SendOkBroken() { *kUartDataBroken = 'O'; *kUartDataBroken = 'K'; }
void SendOk() { *kUartData = 'O'; *kUartData = 'K'; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
