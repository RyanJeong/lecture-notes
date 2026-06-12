#include <stdio.h>

/* count characters in input; 2nd version */
int main(void)
{
    double nc; /* use double to allow for large counts rather than int / long */

    for (nc = 0; getchar() != EOF; ++nc) {}
    printf("%.0f\n", nc);

    return 0;
}
