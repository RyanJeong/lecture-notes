#include <stdio.h>

/* copy input to output; 2nd version */
int main(void)
{
    int c; /* instead of char type */

    /* the != operator has a higher precedence than =, so parentheses are needed
       to ensure that the = operator is evaluated before the != operator. */
    while ((c = getchar()) != EOF)
        putchar(c);

    return 0;
}
