#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

/* count lines, words, and characters in input */
int main(void)
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*1*/ nl = nw = (nc = 0);
    /*2*/ nl = (nw = (nc = 0));
    /*3*/ (nl = (nw = (nc = 0)));
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if ((c == ' ') || (c == '\n') || (c == '\t')) {
        /* ... */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (cond_1) {
        /* ... */
    } else {
        if (cond_2) {
            /* ... */
        }
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if ((c == ' ') || (c == '\n') || (c == '\t')) {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);

    return 0;
}
