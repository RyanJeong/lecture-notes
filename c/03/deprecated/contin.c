#include <stdio.h>

int main(void)
{
    int i, a[100];

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (i = 0; i < 100; ++i) {
        if (a[i] >= 0) {
            /* only positive elements present here. */
        }
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (i = 0; i < 100; ++i) {
        if (a[i] < 0)
            continue; /* skip negative elements */

        /* only positive elements present here. */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}