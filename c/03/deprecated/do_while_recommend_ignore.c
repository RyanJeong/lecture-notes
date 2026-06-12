void do_while_recommend()
{
    char s[1024];
    int i = 0;
    int n = 123;

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* do-while loop using a single statement */
    do
        s[i++] = (n % 10) + '0';
    while ((n /= 10) > 0); /* It can be confused with a while without a body */
#endif                     /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* do-while loop using a compound statement */
    do {
        s[i++] = (n % 10) + '0';
    } while ((n /= 10) > 0);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return;
}
