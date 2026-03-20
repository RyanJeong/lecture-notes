#include <stdio.h>

int main(void)
{
    printf("This is a backslash: \\, single quote: \', double quote: \", "
           "question mark: \?\n");
    printf("Null character in the middle \0(this part will be ignored)\n");
    putchar('\n');
    putchar('\''); /* putchar('''); -> error */
    putchar('\n');
    printf("??!\n" /* you need to use backslash in C90 to avoid trigraph */
           "\?\?!\n");

    return 0;
}