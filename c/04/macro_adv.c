#include <stdio.h>
#define GREETING_MESSAGE               \
    do {                               \
        printf("Hello, World!\n");     \
        printf("Have a great day!\n"); \
    } while (0)

void greeting(int flag)
{
    if (flag)
        GREETING_MESSAGE;
}
