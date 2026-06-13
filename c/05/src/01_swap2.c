#include <stdio.h>

/* Parameters are local variables but are pointers;
 * changes affect the arguments. */
void swap(int *px, int *py)
{
    int temp = *px;
    *px = *py;
    *py = temp;
}

int main(void)
{
    int a = 10, b = -200;

    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b); /* `a` is now -200 and `b` is 10 */

    return 0;
}
