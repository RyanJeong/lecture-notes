#include <ctype.h> /* for isspace(), tolower() */
#include <stdio.h>
#include <stdlib.h> /* for srand(), rand() */
#include <time.h>   /* for time(NULL) */

enum {
    ROCK,     /* 0, SCISSORS > ROCK > PAPER */
    PAPER,    /* 1, ROCK > PAPER > SCISSORS */
    SCISSORS, /* 2, PAPER > SCISSORS > ROCK */
    SHAPES    /* 3 */
};

int main(void)
{
    int c;
    int shape;  /* computer's hand shape: rock, paper, or scissors */
    int cnt;    /* number of rounds played */
    double win; /* number of rounds the player won */

    printf("*** ROCK PAPER SCISSORS ***\n");
    c = 'h';
    cnt = 0;
    win = 0.0;
    srand(time(NULL));
    do {
        if (isspace(c))
            continue;

        /* 'A' -> 'a' */
        if (isupper(c))
            c = tolower(c);
        switch (c) {
        case 'r':
        case 'p':
        case 's':
            shape = (rand() % SHAPES);
            ++cnt;
            c = ((c == 'r') ? ROCK : ((c == 'p') ? PAPER : SCISSORS));
            printf("[#%3d] Player: [%s], Computer: [%s], %s\n", cnt,
                   c == ROCK ? "ROCK" : (c == PAPER ? "PAPER" : "SCISSORS"),
                   shape == ROCK ? "ROCK"
                                 : (shape == PAPER ? "PAPER" : "SCISSORS"),
                   c == shape
                       ? "Draw!"
                       : (c == (shape + 1) % SHAPES ? (++win, "Player wins!")
                                                    : "Computer wins!"));
            break;
        case 'e':
            printf("Exit the game!\n");
            if (cnt) {
                printf("Played: %3d, Win rate: %.2f%%\n", cnt,
                       (win / (double) cnt) * 100.0);
            }
            break;
        default:
            if (c != 'h')
                printf("Wrong input!\n");
            printf("r: Rock, p: Paper, s: Scissors, h: Help, e: Exit\n");
            break;
        }
        if (c == 'e')
            break;
    } while ((c = getchar()) != EOF);

    return 0;
}
