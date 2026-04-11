#include <stdio.h>

void foo(int a, int b, int c)
{
    printf("%d %d %d\n", a, b, c);
    return;
}

int main(void)
{
    int a, b, c;
    a = b = c = 100;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* The function `foo` takes three arguments, with the second argument set
       to 5. */
    foo(a, (b = 3, b + 2), c);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
