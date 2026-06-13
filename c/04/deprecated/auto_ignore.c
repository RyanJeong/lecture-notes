void foo(void)
{
#if 1               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    auto int x = 1; /* same as: int x = 1; */
#endif              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
