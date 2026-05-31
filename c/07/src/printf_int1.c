#include <stdio.h>

int main(void)
{
#if 1                           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    printf(":%d:\n", 100);      /* >:100:     */
    printf(":%6d:\n", 100);     /* >:   100:  */
    printf(":%-6d:\n", 100);    /* >:100   :  */
    printf(":%6d:\n", 1000000); /* >:1000000: */

    printf(":%*d:\n", 3, 1000000);     /* >:1000000:    */
    printf(":%*d:\n", 7, 1000000);     /* >:1000000:    */
    printf(":%*.10d:\n", 10, 1000000); /* >:0001000000: */

    printf(":%.5d:\n", 12);        /* >:00012:     */
    printf(":%5.5d:\n", 1234);     /* >:01234:     */
    printf(":%8.5d:\n", 1234);     /* >:   01234:  */
    printf(":%-8.5d:\n", 1234);    /* >:01234   :  */
    printf(":%8.5d:\n", 123456);   /* >:  123456:  */
    printf(":%-8.5d:\n", 123456);  /* >:123456  :  */
    printf(":%8d:\n", -123456);    /* >: -123456:  */
    printf(":%8.8d:\n", -123456);  /* >:-00123456: */
    printf(":%-8d:\n", -123456);   /* >:-123456 :  */
    printf(":%-8.8d:\n", -123456); /* >:-00123456: */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}
