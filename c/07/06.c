#include <stdio.h>

int main(void)
{
    char str[100]; /* NB: str must be big enough to receive the result */
    int len, a, b;

    a = 3, b = 5;
    len = sprintf(str, "%d + %d = %d", a, b, a + b);
    printf("%s, len: %d\n", str, len); /* >3 + 5 = 8, len : 9 */

    return 0;
}
