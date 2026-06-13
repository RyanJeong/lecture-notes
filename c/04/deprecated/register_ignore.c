void foo(void)
{
#if 1                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    register int x = 1; /* just a hint to the compiler to store `x` in a
                           register; often ignored by modern compilers */
#endif                  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
