#include <stdio.h>

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int d, m, y;

    /* Suppose the user inputs: 05/15/21 */
    scanf("%d/%d/%d", &m, &d, &y);
    printf("m: %d, d: %d, y: %d\n", m, d, y); /* >m: 5, d: 15, y: 21 */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Suppose the user inputs: 05 15 21 */
    scanf("%d/%d/%d", &m, &d, &y);
    printf("m: %d, d: %d, y: %d\n", m, d, y); /* >m: 5, d: ???, y: ??? */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
