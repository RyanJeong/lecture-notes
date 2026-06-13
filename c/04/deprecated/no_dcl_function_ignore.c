#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int foo(void)
{
    return 100;
}

double bar(void)
{
    return 3.14;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Missing function declaration; both return types are assumed to be int */
    int foo_val = foo();    /* OK: foo() returns 100 */
    double bar_val = bar(); /* Error: bar() returns garbage (not 3.14) */
#endif                      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}