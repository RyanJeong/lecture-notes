#include <stdio.h>
#include <string.h> /* for strcat() */

int main(void)
{
    char str1[100] = "Hello, ";
    char str2[100] = "World!";

    strcat(str1, str2);
    printf("%s", str1); /* Hello, World! */

    return 0;
}
