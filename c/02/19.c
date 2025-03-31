#include <stdio.h>

int main(void)
{
    int n = 24, i;

    /* We're going to print some formatted contents as below:

        1  2  3  4  5  6  7  8  9 10
       11 12 13 14 15 16 17 18 19 20
       21 22 23 24

       We could consider something like this:

       for (i = 1; i <= n; ++i) {
           if (!(i % 10) || i == n)
               printf("%2d\n", i);
           else
               printf("%2d ", i);
       }

       Though the following form appears much nicer:
    */
    for (i = 1; i <= n; ++i)
        printf("%2d%c", i, (!(i % 10) || i == n) ? '\n' : ' ');

    return 0;
}
