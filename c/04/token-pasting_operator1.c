#include <stdio.h>

#define DEBUG(var, type) DEBUG_##type(var)
#define DEBUG_INT(var) printf(#var " = %d\n", (var))
#define DEBUG_FLOAT(var) printf(#var " = %.2f\n", (var))
#define DEBUG_CHAR(var) printf(#var " = '%c'\n", (var))

int main(void)
{
    int age = 20;          /* age = 20 */
    float height = 175.5f; /* height = 175.50 */
    char grade = 'A';      /* grade = 'A' */

    DEBUG(age, INT);
    DEBUG(height, FLOAT);
    DEBUG(grade, CHAR);

    return 0;
}
