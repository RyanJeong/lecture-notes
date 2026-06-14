#include <ctype.h> /* for isspace(), isdigit() */
#include <stdio.h>

/* NB: Reuse previously implemented functions: getch(), ungetch() */
int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) {}
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */

        return 0; /* return 0 if invalid */
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);

    return c; /* c: first non-digit character after a valid number, or EOF */
}
