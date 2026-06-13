void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int val = 10;
    int a[5];
    int *p = a;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    *p++ = val; /* push val onto stack */
#endif          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    a[0] = 5;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    val = *--p; /* pop top of stack into val */
#endif          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
