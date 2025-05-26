#include <stdio.h>

struct data {
    int id;
    char *str;
};

int main(void)
{
    char buf1[] = "abc";
    char buf2[] = "def";
    char buf3[] = "xyz";

    struct data arr[3] = { { 1, buf1 }, { 2, buf2 }, { 3, buf3 } };
    struct data *p = arr;

    ++p->id;     /* increments `id`, not p -> implied: ++(p->id) */
    (++p)->id;   /* increments `p` before accessing `id` */
    (p++)->id;   /* increments `p` after accessing `id` */
    *p->str;     /* fetches whatever `str` points to */
    *p->str++;   /* accesses *p->str, then increments `str` */
    (*p->str)++; /* increments the character that `str` points to */
    *p++->str;   /* accesses `str`, then increments `p` */

    return 0;
}
