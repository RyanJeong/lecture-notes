#include <stdio.h>

int main(void) /* rudimentary calculator */
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    double sum, v;

    sum = 0;
    /* Suppose the user inputs: +1  -2  3.0  4.5e1  s */
    while (scanf("%lf", &v) == 1)
        printf("\t%.2f\n", sum += v); /* >1.00
                                         >-1.00
                                         >2.00
                                         >47.00 */
    /* Expected numbers but encountered a non-numeric input (`s`), terminate the
     * loop and `s` still in the input buffer */
    putchar(getchar()); /* >s     */
#endif                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
