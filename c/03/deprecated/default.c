#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int num = 3;

    switch (num) {
    case 1:
        printf("num is 1.\n");
        break;
    default:
        printf("No matching number. (Default)\n");
        /* What happens if there's no break here? */
    case 2:
        printf("num is 2.\n");
        break;
    }  /* Output: No matching number. (Default)\nnum is 2. (fall-through) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
