void foo(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int matrix[4][3] = {
        { 10, 20, 30 },   /* Initializes matrix[0] -> row 0 */
        { 40, 50, 60 },   /* Initializes matrix[1] -> row 1 */
        { 70, 80, 90 },   /* Initializes matrix[2] -> row 2 */
        { 100, 110, 120 } /* Initializes matrix[3] -> row 3 */
    };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) matrix;
}

void bar(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int matrix[][2] = { { 10, 20 }, { 30, 40 }, { 50, 60 }, { 70, 80 } };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) matrix;
}

void qux(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int cube[2][2][3] = {
        {
            { 10, 20, 30 }, /* Initializes cube[0][0] -> depth 0, row 0 */
            { 40, 50, 60 }  /* Initializes cube[0][1] -> depth 0, row 1 */
        },
        {
            { 70, 80, 90 },   /* Initializes cube[1][0] -> depth 1, row 0 */
            { 100, 110, 120 } /* Initializes cube[1][1] -> depth 1, row 1 */
        }
    };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) cube;
}

void quz(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    char *name[] = { "Illegal month", "Jan", "Feb", "Mar" };
    char aname[][15] = { "Illegal month", "Jan", "Feb", "Mar" };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) aname;
    (void) name;
}
