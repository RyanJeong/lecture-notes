#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
    struct point temp;

    /* reusing 'x' and 'y' as both parameter and member names emphasizes the
     * mapping */
    temp.x = x;
    temp.y = y;

    return temp;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* addpoints: add two points */
struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;

    return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
    return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <stdio.h>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* printpoint: print a point */
void printpoint(struct point *pt)
{
    printf("(%d, %d)\n", (*pt).x, (*pt).y);
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */