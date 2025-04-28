#include <stdio.h>

#define DECODE(s, t, u, m, p, e, d) m##s##u##t
#define begin DECODE(a, n, i, m, a, t, e)

int begin(void)
{
    printf("Stumped?\n");

    return 0;
}
