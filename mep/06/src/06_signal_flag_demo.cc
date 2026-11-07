#include <csignal>
#include <cstdio>
#include <unistd.h>

volatile std::sig_atomic_t g_stop = 0;

void HandleAlarm(int) { g_stop = 1; }

int main() {
  if (std::signal(SIGALRM, HandleAlarm) == SIG_ERR) {
    std::perror("signal");
    return 1;
  }
  alarm(1);
  while (g_stop == 0) {}
  std::puts("Signal received; the loop stopped.");
  return 0;
}
