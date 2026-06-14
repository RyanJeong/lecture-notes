#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

/* count lines, words, and characters in input */
int main(void)
{
    int c, nl, nw, nc, state;

    state = OUT;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    nl = nw = nc = 0;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
        if ((c == ' ') || (c == '\n') || (c == '\t')) {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            ++nw;
        }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    }
    printf("%d %d %d\n", nl, nw, nc);

    return 0;
}
