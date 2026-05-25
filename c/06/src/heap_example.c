#include <stdio.h>
#include <stdlib.h> /* for malloc, free */

int main(void)
{
    int i, n = 5;
    int *pa = (int *) malloc(n * sizeof(int));

    if (pa == NULL) {
        /* Return NULL if malloc fails */
        printf("malloc failed.\n");
    } else {
        for (i = 0; i < n; ++i) {
            pa[i] = i * 10;
            printf("pa[%d] = %d\n", i, pa[i]);
        }
        free(pa);
        pa = NULL; /* Prevent use-after-free */
    }

    return 0;
}
