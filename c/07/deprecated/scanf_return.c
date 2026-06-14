#include <stdio.h>

void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a, b, ret;
    /* Suppose the user inputs: 10  30  20 */
    while ((ret = scanf("%d %d", &a, &b)) == 2)
        printf("%d + %d = %d (%d)\n", a, b, a + b, ret); /* >10 + 30 = 40 (2) */
    printf("ret: %d\n", ret);                            /* >ret: 1 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void bar(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a, b, ret;
    /* Suppose the user inputs: 10  30  20 */
    while ((ret = scanf("%d %d", &a, &b)) != EOF)
        printf("%d + %d = %d (%d)\n", a, b, a + b, ret); /* >10 + 30 = 40 (2)
                                                          * >20 + 30 = 50 (1) */
    printf("ret: %d\n", ret);                            /* >ret: -1 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

int main(void)
{
    foo();
    bar();
    return 0;
}
