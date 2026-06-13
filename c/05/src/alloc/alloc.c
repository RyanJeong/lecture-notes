#include "alloc.h"

#if 1              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <stdio.h> /* for NULL */

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

/* return pointer to n characters */
char *alloc(int n)
{
    /* it fits */
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        /* old p */
        return allocp - n;
    }
    /* not enough room */
    return NULL; /* indicates allocation failure */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* free storage pointed to by p */
void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
