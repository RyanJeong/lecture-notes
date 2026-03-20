#include <stdio.h>
#include <string.h> /* for strlen() */

int main(void)
{
    char str[100] = "Hello";
    int str_len = strlen(str);

    printf("%s's length is %d.\n", str, str_len); /* Hello's length is 5. */

    return 0;
}
