#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct data {
    int id;
    char *str;
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void foo(void)
{
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char str[] = "abc def xyz";
    struct data arr[3] = { { 1, str }, { 4, str + 4 }, { 8, str + 8 } };
    struct data *p = arr;

    ++p->id;     /* res: 2, increments `id`, not p -> implied: ++(p->id) */
    (++p)->id;   /* res: 4, increments `p` before accessing `id` */
    (p++)->id;   /* res: 4, increments `p` after accessing `id` */
    *p->str;     /* res: 'x', fetches whatever `str` points to */
    *p->str++;   /* res: 'x', accesses *p->str, then increments `str` */
    (*p->str)++; /* res: 'y', increments the character that `str` points to */
    *p++->str;   /* res: 'z', accesses `str`, then increments `p` */
    /* now `p` points past the last element of the array */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
