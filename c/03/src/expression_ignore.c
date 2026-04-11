#include <stdio.h>

int main(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  a = 10 /* Assignment expression: evaluates to 10 (the assigned value) */
  b + c  /* Addition expression: evaluates to the sum of `b` and `c` */
  x++    /* Post-increment expression: evaluates to the current value of `x`,
            then increments `x` by 1 */
  f(x)   /* Function call expression: evaluates to the return value of function
            `f` with argument `x` */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    int x, i;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* A statement = <expression(opt)> + ; */
    x = 0;                   /* assignment expression + ; */
    ++i;                     /* pre-increment expression + ; */
    printf("Hello, world!"); /* function call expression + ; */

    /* Following statements are also valid (use empty expressions) */
    ;  /* (empty expression) + ; */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}
