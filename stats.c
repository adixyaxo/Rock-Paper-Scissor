#include <stdio.h>
#include <stdlib.h>
#include "auth.c"

// this is the file which would handle all the onging stats and update them accordingly
/*
HARD MODE
for every win user gets 10 points
for every tie user gets 0 points
for every loss user gets -10 points

NORMAL MODE
for every win user gets 10 points
for every tie user gets 1 points
for every loss user gets -5 points

EASY MODE
for every win user gets 10 points
for every tie user gets 5 points
for every loss user gets 0 points
*/
int difficulty_level;
void difficulty() {
    int n;
    printf("Choose one difficulty level from the following\nHard :: 1\nNormal :: 2\nEasy :: 3\n");
    scanf("%d",&n);
    printf("\n\n");
    if (n==1 || n==2 || n==3)
    {
        difficulty_level=n;
    }
    else
    {
        printf("Invalid Choice, Please choose again\n");
        difficulty();
    }
}

void win()
{
    user.wins += 1;
    user.score += 10;
}

void lost()
{
    user.losses += 1;
    if (difficulty_level == 1)
    {
        user.score -= 10;
    }
    else if (difficulty_level == 2)
    {
        user.score -= 5;
    }
    else if (difficulty_level == 3)
    {
        user.score += 0;
    }
}

void tie()
{
    user.ties += 1;
    if (difficulty_level == 1)
    {
        user.score += 0;
    }
    else if (difficulty_level == 2)
    {
        (user.score) += 1;
    }
    else if (difficulty_level == 3)
    {
        (user.score) += 5;
    }
    
}

void displaystats()
{
    printf("\n\n----- YOUR STATS -----\n");
    printf("Name: %s\n", user.name);
    printf("High Score: %d\n", (user.high_score));
    printf("Number of Matches Played: %d\n", (user.no_matches));
    printf("Number of Rounds Played: %d\n", (user.no_rounds));
    printf("Wins: %d\n", (user.wins));
    printf("Losses: %d\n", (user.losses));
    printf("Ties: %d\n", (user.ties));
    printf("Total Score: %d\n", (user.score));
    printf("----------------------\n\n");
}