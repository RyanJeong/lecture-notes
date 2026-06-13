#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* Parameters are local variables; changes do not affect the arguments. */
void swap(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main(void)
{
    int a = 10, b = -200;

#if 1           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    swap(a, b); /* `a` is still 10 because swap() uses call by value */
#endif          /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    return a;
}
