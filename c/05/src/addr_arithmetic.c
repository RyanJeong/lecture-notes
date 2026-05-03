void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a[10];
    int *p = &a[0]; /* points to first element */
    int *q = &a[2]; /* points to third element */

    int diff = q - p;          /* result: 2 elements apart */
    int p_is_before_q = p < q; /* true, because p comes before q in the array */
    int *end = &a[10];         /* valid pointer, points just past the array */
    while (p++ < end) {
        /* safe iteration from a[0] to a[9] */
    }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    (void) diff;
    (void) p_is_before_q;
}
