#include "alloc.h"

int main(void)
{
    /* `alloc` returns address 0x08AF1EE8 after allocating 7 bytes */
    char *p = alloc(7);

    /* sets `allocp` to 0x08AF1EEA, meaning 5 bytes were released */
    afree(p + 2);

    return 0;
}
