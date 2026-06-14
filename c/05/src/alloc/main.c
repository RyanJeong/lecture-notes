#include "alloc.h"

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* `alloc` returns address 0x08AF1EE8 after allocating 7 bytes */
    char *p = alloc(7);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* sets `allocp` to 0x08AF1EEA, meaning 5 bytes were released */
    afree(p + 2);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
