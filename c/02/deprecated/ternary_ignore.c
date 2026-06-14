#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n = 100;
    float f = 3.14;

    (n > 0) ? f : n; /* the evaluated type is float */
#endif               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int n = 2;

    /* You can replace this if-else statement with ternary operator:
       if (n == 1)
           printf("You have %d item\n", n);
       else
           printf("You have %d items\n", n); */
    printf("You have %d item%c\n", n, (n == 1) ? '\0' : 's');
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}
