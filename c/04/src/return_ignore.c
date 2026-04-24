#if 1                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int sum(int a, int b) /* callee */
{
    return a + b; /* return value */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main(void)
{
#if 1                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int result = sum(5, 10); /* caller (return value is assigned to `result`) */
#endif                       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return 0;
}