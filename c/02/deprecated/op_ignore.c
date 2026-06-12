#include <stdio.h>

int prefix(int i)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* ++i: Increments the value first */
    i = i + 1;
    return i;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}

int postfix(int i)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* i++: Uses the value first, then increments */
    int temp = i;
    i = i + 1;
    return temp;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}

int main(void)
{
#if 1              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (!valid) {} /* preferred style */

    if (valid == 0) {} /* also correct, but less readable */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a, b;

    b = 3;
    a = b++; /* a = 3, b = 4 */
    a = b;   /* a = 4, b = 4 */
    a = ++b; /* a = 5, b = 5 */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    int yyval[100];
    int vvpv[100];
    int p1, p2, p3, p4;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    yyval[yypv[p3 + p4] + yypv[p1]] = yyval[yypv[p3 + p4] + yypv[p1]] + 2;
    yyval[yypv[p3 + p4] + yypv[p1]] += 2;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    int x, y;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    x *= y + 1;
    /*
     * 1. x *= (y + 1)
     * 2. x = x * (y + 1)
     */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (x >>= y != 0) { /* do something */ }
    /*
     * 1. x >>= (y != 0)
     * 2. x = x >> (y != 0)
     */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}
