#include <stdio.h>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
char *fgets(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs = s;

    while (--n > 0 && (c = getc(iop)) != EOF)
        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';

    return (c == EOF && cs == s) ? NULL : s;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int fputs(const char *s, FILE *iop)
{
    int c;
    while ((c = *s++))
        putc(c, iop);

    return ferror(iop) ? EOF : 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
