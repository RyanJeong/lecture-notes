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
