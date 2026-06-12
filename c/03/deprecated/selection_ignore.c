#include <stdio.h>

int main(void)
{
    int x, y, z, a, b, n;
#if 1          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (x > 0) /* statement -> expression-statement */
        y = 1;

    if (x > 0) /* statement -> compound-statement */ {
        int y = 10;
        y += 5;
    }

    if (x > 0) /* statement -> selection-statement */
        if (y > 0)
            z = 1;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (n > 0)
        if (a > b)
            z = a;
    else
        z = b;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (n > 0)
        if (a > b)
            z = a;
        else
            z = b;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    if (n > 0) {
        if (a > b)
            z = a;
    } else
        z = b;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    switch (100)
    case 200: /* `case` determines where the execution jumps to when the switch
                 expression matches the case label */
        printf("switch statement with case label");

    switch (300)
    default: /* `default` determines where the execution jumps to when no case
                label matches */
        printf("switch statement with default label");
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
