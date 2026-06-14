/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low = 0, high = n - 1, mid;

    /* WRONG: closed-interval setup, but high = mid (the - 1 is missing) */
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid; /* BUG: should be mid - 1 */
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1; /* no match */
}
