int main(void)
{
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
    struct {
        unsigned int a : 1;
        unsigned int b : 2;
        unsigned int : 0;
        unsigned int c : 1;
        unsigned int d : 8;
    } bits = { 0 };

    bits.a = 1;   /*         1 */
    bits.b = 2;   /*        10 */
    bits.c = 1;   /*         1 */
    bits.d = 128; /* 1000 0000 */
#endif            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

    (void) bits; /* Suppress unused variable warning */
    return 0;
}
