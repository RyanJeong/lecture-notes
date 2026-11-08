#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Set by the button interrupt handler, read by the main loop.
volatile bool g_button_pressed = false;

// Registered in the interrupt vector table: the hardware calls it, not main().
void ButtonIsr() { g_button_pressed = true; }

void WaitForButton() {
  while (!g_button_pressed) {
    // Nothing in this loop writes the flag; only ButtonIsr() does.
  }
  g_button_pressed = false;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
