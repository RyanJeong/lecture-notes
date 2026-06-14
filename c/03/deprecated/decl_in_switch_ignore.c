#include <stdio.h>

int main(void)
{
    switch (1) {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    case 1:
        int x = 10; /* Invalid: declarations are not statements */
        break;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    case 1: {
        int x = 10; /* Valid: compound statement can contain declarations */
        break;
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    break;
    }

    return 0;
}
