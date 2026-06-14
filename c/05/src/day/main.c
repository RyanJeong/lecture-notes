#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
char *month_name(int n);

int main(void)
{
    int year = 2025;
    int month = 5;
    int day = 21;
    int day_year = day_of_year(year, month, day);

    printf("Day of year from %s and %d is %d.\n", month_name(month), day,
           day_year);
    day_year = 200;
    month_day(year, day_year, &month, &day);
    printf("Month, day from day of year (%d) are %s and %d.\n", day_year,
           month_name(month), day);

    return 0;
}
