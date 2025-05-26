#include <stdio.h>

struct point {
    int x;
    int y;
};

void print(struct point pt) /* function argument: passing structure by value */
{
    printf("Point: (%d, %d)\n", pt.x, pt.y); /* member access: via . operator */
}

struct point origin(void) /* function return: returning a structure by value */
{
    /* initialization: using a list of initializers */
    struct point zero = { 0, 0 };
    return zero;
}

int main(void)
{
    struct point p1 = origin(); /* initialization: from function return value */
    struct point p2 = p1; /* initialization: by copying another structure */
    struct point *pp;     /* declaration: pointer to `struct point` */

    p1 = p2;        /* assignment: entire structure assignment */
    print(p1);      /* function argument: passing structure by value */
    pp = &p2;       /* address-of: take address of structure */
    pp->x += pp->y; /* member access: via -> operator */
    return 0;
}
