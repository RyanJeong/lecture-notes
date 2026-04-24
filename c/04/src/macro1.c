#include <stdio.h>

/* NB: the last one is an expression */
#define GREETING_MESSAGE       \
    printf("Hello, World!\n"); \
    printf("Have a great day!\n")

void greeting(void)
{
    GREETING_MESSAGE;
}
