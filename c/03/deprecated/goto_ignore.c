#include <stdio.h>

int main(void)
{
    goto jump_before_return_stmt;
    printf("Hello, world!\n"); /* Not executed because of the goto statement */

jump_before_return_stmt:
    return 0; /* identifier : statement (labeled-statement) */
}

void without_goto(void)
{
    int a[100], b[100], n, m, i, j, found;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    for (found = i = 0; (i < n) && !found; ++i) {
        for (j = 0; (j < m) && !found; ++j) {
            if (a[i] == b[j])
                found = 1;
        }
    }
    if (!found)
        return; /* didn't find any common element */
    printf("got one: a[i] == b[j]\n");
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return;
}

void with_goto(void)
{
    int a[100], b[100], n, m, i, j, found;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /*
     * Goto could be replaced with a sentinel variable or with a function call.
     */
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (a[i] == b[j])
                goto found;
        }
    }
    return; /* didn't find any common elements */
found:
    printf("got one: a[i] == b[j]\n");
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return;
}
