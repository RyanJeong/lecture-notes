#include <stdio.h> /* EOF is a negative integer constant defined in stdio.h */

/* copy input to output; 1st version */
int main(void)
{
    int c;

    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }

    return 0;
}
