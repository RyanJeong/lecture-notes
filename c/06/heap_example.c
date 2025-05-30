#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *pa, *pb;
    int i, n = 5;

    pa = (int *) malloc(n * sizeof(int));
    if (pa == NULL) {
        printf("malloc failed.\n");
    } else {
        for (i = 0; i < n; ++i) {
            pa[i] = i * 10;
            printf("pa[%d] = %d\n", i, pa[i]);
        }
        free(pa);
        pa = NULL; /* Prevent use-after-free */
    }

    pb = (int *) calloc(n, sizeof(int));
    if (pb == NULL) {
        printf("calloc failed.\n");
    } else {
        for (i = 0; i < n; ++i)
            printf("pb[%d] = %d\n", i, pb[i]);
        free(pb);
        pb = NULL; /* Prevent use-after-free */
    }

    return 0;
}
