#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int cmp(const void *s, const void *t)
{
    return (*(int *) s - *(int *) t);
}

int main(void)
{
    int arr[SIZE] = { 32, 15, 31, 76, 3, 99, 23, -56, -28, 2 };
    int i, target;

    printf("Before: ");
    for (i = 0; i < SIZE; ++i)
        printf("%3d%c", arr[i], i == SIZE - 1 ? '\n' : ' ');
    qsort(arr, SIZE, sizeof(int), cmp);
    printf("After : ");
    for (i = 0; i < SIZE; ++i)
        printf("%3d%c", arr[i], i == SIZE - 1 ? '\n' : ' ');

    target = 2;
    printf("%d %s\n", target,
           (bsearch(&target, arr, SIZE, sizeof(int), cmp) ? "is found"
                                                          : "is not found"));
    target = 16;
    printf("%d %s\n", target,
           (bsearch(&target, arr, SIZE, sizeof(int), cmp) ? "is found"
                                                          : "is not found"));

    return 0;
}
