#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* my_math.h */
int add(int a, int b); /* a function declaration */
#define PI 3.14159     /* a constant definition */
#endif                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* 1. Include a custom header file using relative paths */
#include "my_math.h" /* include my_math.h from the current directory */

/* 2. Include a custom header file using absolute paths */
#include "/home/docker/workspace/proj_math/include/my_math.h"
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* my_math.c */
#include "my_math.h"

double get_pi(void)
{
    return PI;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* my_math.i */
double get_pi(void);
double get_pi(void)
{
    return 3.14;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
