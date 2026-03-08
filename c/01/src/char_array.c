#include <stdio.h>

int main(void)
{
    char arr1[100] = "Hello";
    char arr2[3];

    arr2[0] = 'H';
    arr2[1] = 'i';
    arr2[2] = '\0';

    printf("%s\n", arr1); /* Output: Hello */
    printf("%s\n", arr2); /* Output: Hi */

    return 0;
}
