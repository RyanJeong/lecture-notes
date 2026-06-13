void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int zero_initialized[5] = { 1, 2 }; /* size: 5 */
                                        /* elements: [1, 2, 0, 0, 0] */

    int fully_initialized[3] = { 1, 2, 3 }; /* size: 3 */
                                            /* elements: [1, 2, 3] */

    char inferred_size[] = "abcd"; /* size: 5 (includes null terminator '\0') */
                                   /* elements: ['a', 'b', 'c', 'd', '\0'] */
#endif                        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    (void) inferred_size;     /* Avoid unused variable warning. */
    (void) zero_initialized;  /* Avoid unused variable warning. */
    (void) fully_initialized; /* Avoid unused variable warning. */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    /* Error: too many initializers for array of size 3 */
    int invalid_array[3] = { 1, 2, 3, 4, 5, 6 }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}