#include <ctype.h> /* for isspace(), isdigit() */

/* atof: convert string s to double */
double atof(char s[])
{
    double digits_value, decimal_scale;
    int i, sign;

    for (i = 0; isspace(s[i]); ++i) {} /* skip white space */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        ++i;
    for (digits_value = 0.0; isdigit(s[i]); i++)
        digits_value = 10.0 * digits_value + (s[i] - '0');
    i += (s[i] == '.'); /* skip decimal point */
    for (decimal_scale = 1.0; isdigit(s[i]); i++) {
        digits_value = 10.0 * digits_value + (s[i] - '0');
        decimal_scale *= 10;
    }

    return sign * (digits_value / decimal_scale);
}
