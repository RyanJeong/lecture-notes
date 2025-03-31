#include <stdio.h>

int main()
{
    printf("%d + %d = %d\n", 5, 3, 5 + 3); /* Expected: 8 */
    printf("%d - %d = %d\n", 5, 3, 5 - 3); /* Expected: 2 */
    printf("%d * %d = %d\n", 5, 3, 5 * 3); /* Expected: 15 */
    printf("%d / %d = %d\n", 6, 3, 6 / 3); /* Expected: 2 */
    printf("%d / %d = %d\n", 7, 4, 7 % 4); /* Expected: 3 */

    return 0;
}
