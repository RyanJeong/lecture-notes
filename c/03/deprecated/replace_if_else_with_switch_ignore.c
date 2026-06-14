#include <stdio.h>

int main(void)
{
    char c;
    int i, ndigit[10], nwhite, nother;

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* You can replace the following phrase with `switch`:
    if (c >= '0' && c <= '9')
        ++ndigit[c - '0'];
    else if ((c == ' ') || (c == '\n') || (c == '\t'))
        ++nwhite;
    else
        ++nother; */

    switch (c) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        ++ndigit[c - '0'];
        break;
    case ' ': case '\n': case '\t':
        ++nwhite;
        break;
    default:
        ++nother;
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}