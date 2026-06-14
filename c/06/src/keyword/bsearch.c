#include <string.h>

#include "key.h"

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* binsearch: find word in tab[0]...tab[n-1] */
struct key *binsearch(char *word, struct key tab[], int n)
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;

    while (low < high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return NULL;
}
