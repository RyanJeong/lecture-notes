#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char str1[2], str2[10], str3[10];
    int a, b, c;

    /* Suppose the user inputs: suppression */
    scanf("%2c %*2c %4s %6s", str1, str2, str3);
    printf("%c%c %s %s\n", str1[0], str1[1], str2, str3); /* >su ress ion */

    /* Suppose the user inputs: 123 456789 */
    scanf("%2d %d %*4d %d", &a, &b, &c);
    printf("%d %d %d\n", a, b, c); /* >12 3 89 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
