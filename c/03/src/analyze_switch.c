#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*   switch (expression) compound-statement */
    switch (1) {
    case 1:
        putchar('A'); /* case constant-expression : expression-statement */
        break;        /* jump-statement */
    case 2:
        putchar('B'); /* case constant-expression : expression-statement */
        break;        /* jump-statement */
    default:
        putchar('-'); /* default : expression-statement */
    }                 /* -> Compound-statement has 5 statements */
#endif                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}