void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char *pmessage = "now is the time"; /* a pointer */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char amessage[] = "now is the time"; /* an array */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) pmessage;
    (void) amessage;
}