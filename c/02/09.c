/* Simplified example; not actual implementation(s). */
/* tolower: convert c to lower case; ASCII only */
int tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (c + 'a' - 'A');
    else
        return c;
}
