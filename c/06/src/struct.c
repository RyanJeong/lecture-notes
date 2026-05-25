#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* `point` is the struct tag */
struct point {
    int x;
    int y;
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* `struct point` is the struct type */
    struct point p1;      /* `p1` is a variable of type `struct point` */
    struct point p2 = p1; /* `p2` is a variable of type `struct point`
                             initialized with the value of `p1` */
#endif                    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) p2; /* Suppress unused variable warning */

#if 1        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    struct { /* Declare an anonymous structure tpye (not reuseable) */
        int x;
        int y;
    } p3; /* Not reusable: the type has no name */
#endif    /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) p3; /* Suppress unused variable warning */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    struct { int x; int y; } p_a; /* Type A: anonymous struct 1 */
    struct { int x; int y; } p_b; /* Type B: anonymous struct 2 (new type!) */
    p_a = p_b; /* error: `p_a` and `p_b` have different types(incompatible) */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 1       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int id;     /* `id` here is a variable in the ordinary identifier namespace */
struct id { /* `id` here is a tag in the tag namespace */
    int id; /* `id` here is a member in the structure member namespace */
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* The member `x` is initialized to 320. */
/* The member `y` is initialized to 200. */
struct point maxpt = { 320, 200 };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct rect {
    struct point pt1;
    struct point pt2;
};

struct rect screen;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <stdio.h>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void member_access(void)
{
    struct point maxpt = { 10, 20 };
    struct rect screen = { { 0, 0 }, { 30, 40 } };

    /* Accessing member `x` of `maxpt`           (maxpt.x: 10) */
    printf("maxpt.x: %d\n", maxpt.x);
    /* Accessing member `y` of `pt2` of `screen` (screen.pt2.y: 40) */
    printf("screen.pt2.y: %d\n", screen.pt2.y);
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
