#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* grandparent.h */
int foo()
{
    return 100;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* parent.h */
#include "grandparent.h"
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* child.c */
#include "grandparent.h"
#include "parent.h"
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
/* grandparent.h */
#ifndef __GRANDPARENT_H__
#define __GRANDPARENT_H__
int foo()
{
    return 100;
}
#endif /* __GRANDPARENT_H__ */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
