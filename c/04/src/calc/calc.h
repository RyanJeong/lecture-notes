#ifndef CALC_CALC_H
#define CALC_CALC_H

#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

#endif /* CALC_CALC_H */
