#include <stdio.h>

int main(void)
{
retry: /* GCC extension: label-before-declaration; not ISO C */
    /* NB: According to standard C (ANSI C / ISO C), a label must be followed by
     * a *statement*. A declaration like 'int x = 0;' is not a statement.
     * GCC allows this via its language extension (label-before-declaration),
     * but to enforce strict standard compliance, use:
     *   gcc -ansi -pedantic main.c
     */

    int x = 0;
    {
        {
            ++x;
            goto exit; /* Jump to the label defined later in the function */
        }
    }

exit:
    /* Loop again if `x` is less than 5 */
    if (x < 5)
        goto retry;
    printf("Escaped nested blocks after %d attempts.\n", x);

    return 0;
}
