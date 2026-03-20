int main(void)
{
#if 1              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int num_seat;  /* ok */
    float rad_1;   /* ok */
    int 2nd_trial; /* error: invalid suffix "nd_trial" on integer constant */
#endif             /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1                 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int _is_modified; /* ok, but don't use it */
#endif                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1         /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    int a, A; /* ok, `a` and `A` are different variables */
#endif        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    return 0;
}

#if 1              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int max_sum_score; /* Store the highest total score ever */

int sum_score(int score[], int size)
{
    extern int max_sum_score;
    int i, sum = 0;

    for (i = 0; i < size; ++i)
        sum += score[i];
    if (sum > max_sum_score)
        max_sum_score = sum;

    return sum;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
