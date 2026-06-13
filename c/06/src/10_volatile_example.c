#include <signal.h> /* for signal, SIGINT */
#include <stdio.h>

volatile int g_done = 0; /* modified by signal handler */

void handle_sigint(int sig)
{
    g_done = 1;
    (void) sig; /* suppress unused parameter warning */
}

int main(void)
{
    signal(SIGINT, handle_sigint);
    printf("Press Ctrl+C to stop.\n");
    while (!g_done) {
        /* reads g_done from memory on every iteration */
    }
    printf("Caught SIGINT, exiting.\n");

    return 0;
}
