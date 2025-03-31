/* bitcount: faster version of the bitcount */
int bitcount(unsigned x)
{
    int count;

    for (count = 0; x; ++count)
        x &= (x - 1);

    return count;
}
