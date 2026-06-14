#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int count(void)
{
    static int counter = 0; /* block-scope variable with no linkage */
    return ++counter;       /* `counter` retains its value across function calls
                             * because it is declared as static */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* file-scope function with internal linkage (not visible to other files) */
static int global_var = 42;

static void set_global_var(int var)
{
    global_var = var; /* modifies the file-scope variable `global_var` */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
