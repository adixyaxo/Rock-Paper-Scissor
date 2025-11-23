#include <stdio.h>
#include <stdlib.h>
#include "game.c"

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
int difficulty() {
    int n;
    printf("\n\nChoose one difficulty level from the following\nHard :: 1\nNormal :: 2\nEasy :: 3\n");
    scanf("%d",&n);
    printf("\n\n");
    if (n==1 || n==2 || n==3)
    {
        difficulty_level=n;
        return n;
    }
    else
    {
        printf("Invalid Choice, Please choose again\n");
        return difficulty();
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

void highscore()
{
    if (user.score > user.high_score)
    {
        user.high_score = user.score;
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

void mp1win(level)
{
    player1.wins += 1;
    player1.score += 10;
    player2.losses += 1;
    if (level == 1)
    {
        player2.score -= 10;
    }
    else if (level == 2)
    {
        player2.score -= 5;
    }
    else if (level == 3)
    {
        player2.score += 0;
    }
        if (player1.score > player1.high_score)
    {
        player1.high_score = player1.score;
    }
    if (player2.score > player2.high_score)
    {
        player2.high_score = player2.score;
    }
}

void mp2win(level)
{
    player2.wins += 1;
    player2.score += 10;
    player1.losses += 1;
    if (level == 1)
    {
        player1.score -= 10;
    }
    else if (level == 2)
    {
        player1.score -= 5;
    }
    else if (level == 3)
    {
        player1.score += 0;
    }
        if (player1.score > player1.high_score)
    {
        player1.high_score = player1.score;
    }
    if (player2.score > player2.high_score)
    {
        player2.high_score = player2.score;
    }
}

void mtie()
{
    player1.ties += 1;
    player2.ties += 1;
    if (difficulty_level == 1)
    {
        // no score change
    }
    else if (difficulty_level == 2)
    {
        player1.score += 1;
        player2.score += 1;
    }
    else if (difficulty_level == 3)
    {
        player1.score += 5;
        player2.score += 5;
    }
    if (player1.score > player1.high_score)
    {
        player1.high_score = player1.score;
    }
    if (player2.score > player2.high_score)
    {
        player2.high_score = player2.score;
    }
}

void mdisplaystats()
{
    printf("\n\n----- PLAYER 1 STATS -----\n");
    printf("Name: %s\n", player1.name);
    printf("Wins: %d\n", (player1.wins));
    printf("Losses: %d\n", (player1.losses));
    printf("Ties: %d\n", (player1.ties));
    printf("Total Score: %d\n", (player1.score));
    printf("--------------------------\n\n");

    printf("\n\n----- PLAYER 2 STATS -----\n");
    printf("Name: %s\n", player2.name);
    printf("Wins: %d\n", (player2.wins));
    printf("Losses: %d\n", (player2.losses));
    printf("Ties: %d\n", (player2.ties));
    printf("Total Score: %d\n", (player2.score));
    printf("--------------------------\n\n");
}
