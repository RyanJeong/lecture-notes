#if 1              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <stdio.h> /* absolute path to a standard header file */

#include "my_proj.h" /* relative path to a user-defined header file */

#define MY_HEADER "my_header.h"
#include MY_HEADER /* using a macro to include a header file */
#endif             /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define HELLO "Hello, World!"
/* ... */
#undef HELLO /* After this point, the `HELLO` identifier is no longer valid */
#endif       /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#define TOKEN "token"

printf("%s", "TOKEN");   /* the string "TOKEN" is not the token `TOKEN` */
printf("%s", TOKENIZER); /* the token `TOKENIZER` is not the same with the token
                            `TOKEN` */
#endif                   /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */