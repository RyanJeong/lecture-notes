#include <ctype.h> /*  isdigit() */
#include <stdio.h>

int main(void)
{
    int c;
    int cnt; /* number of lotto lines to generate */

    printf("*** LOTTO NUMBER GENERATOR ***\n"
           "How many lines do you want to generate?\n");
    cnt = 0;
    while ((c = getchar()) != EOF) {
        if (!isdigit(c))
            break;
        cnt = (cnt * 10) + (c - '0');
    }
    if (!cnt) {
        printf("Please input a positive number.\n");

        return 1;
    } else {
        printf("%3d", cnt);
    }

    return 0;
}
