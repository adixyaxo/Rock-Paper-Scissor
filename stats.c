#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int gamesplayed;
    int roundsplayed;
    int wins;
    int losses;
    int ties;
} player;


player p1;

void reset()
{
    p1.gamesplayed = 0;
    p1.roundsplayed = 0;
    p1.wins = 0;
    p1.losses = 0;
    p1.ties = 0;
}

void displaystats()
{
    printf("Games Played: %d\n", p1.gamesplayed);
    printf("Rounds Played: %d\n", p1.roundsplayed);
    printf("Wins: %d\n", p1.wins);
    printf("Losses: %d\n", p1.losses);
    printf("Ties: %d\n", p1.ties);
}
