#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* file1.c */
int g_foo = 10;
static int g_bar = 20; /* `g_bar` has internal linkage and is not visible
                          outside this file */

void func(void)
{
    extern int g_foo; /* `extern` is optional because `g_foo` is already visible
                         (but it clarifies that `g_foo` is defined elsewhere) */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* file2.c */
extern int g_foo; /* `extern` is required to use `g_foo` defined in file1.c */
extern int g_bar; /* `g_bar` is not visible here because it has internal linkage
                     -> compile error */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
