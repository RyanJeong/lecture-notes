#include <stdio.h>

int main(void)
{
    int a[5] = { 10, 20, 30, 40, 50 };

    /* Set pointer to point to element at index 2 (i.e., a[2] = 30) */
    int *p = &a[2];

    /* Access relative to array base: a[-1], a[0], a[1] */
    printf("a[-1] = %d\n", a[-1]); /* undefined behavior: before array start */
    printf("a[0]  = %d\n", a[0]);  /* valid: first element (10) */
    printf("a[1]  = %d\n", a[1]);  /* valid: second element (20) */

    /* Access relative to pointer p = &a[2]: p[-1], p[0], p[1] */
    printf("p[-1] = %d\n", p[-1]); /* valid: a[1] = 20 */
    printf("p[0]  = %d\n", p[0]);  /* valid: a[2] = 30 */
    printf("p[1]  = %d\n", p[1]);  /* valid: a[3] = 40 */

    return 0;
}
