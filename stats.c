#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "auth.h"
#include "variable.h"
#include "ui.h"
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
int difficulty()
{
    int n;
    scanui("\n\nChoose one difficulty level from the following\nHard :: 1\nNormal :: 2\nEasy :: 3\n", &n);
    printui("\n\n");
    if (n == 1 || n == 2 || n == 3)
    {
        difficulty_level = n;
        return n;
    }
    else
    {
        printui("Invalid Choice, Please choose again\n");
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
    printui(formatui("\n\n----- YOUR STATS -----\n"));
    printui(formatui("Name: %s\n", user.name));
    printui(formatui("High Score: %d\n", (user.high_score)));
    printui(formatui("Number of Matches Played: %d\n", (user.no_matches)));
    printui(formatui("Number of Rounds Played: %d\n", (user.no_rounds)));
    printui(formatui("Wins: %d\n", (user.wins)));
    printui(formatui("Losses: %d\n", (user.losses)));
    printui(formatui("Ties: %d\n", (user.ties)));
    printui(formatui("Total Score: %d\n", (user.score)));
    printui(formatui("----------------------\n\n"));
}

void mp1win(int level)
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

void mp2win(int level)
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
    printui(formatui("\n\n----- PLAYER 1 STATS -----\n"));
    printui(formatui("Name: %s\n", player1.name));         
    printui(formatui("Wins: %d\n", player1.wins));         
    printui(formatui("Losses: %d\n", player1.losses));     
    printui(formatui("Ties: %d\n", player1.ties));         
    printui(formatui("Total Score: %d\n", player1.score)); 
    printui(formatui("--------------------------\n\n"));

    printui(formatui("\n\n----- PLAYER 2 STATS -----\n"));
    printui(formatui("Name: %s\n", player2.name));         
    printui(formatui("Wins: %d\n", player2.wins));         
    printui(formatui("Losses: %d\n", player2.losses));     
    printui(formatui("Ties: %d\n", player2.ties));         
    printui(formatui("Total Score: %d\n", player2.score)); 
    printui(formatui("--------------------------\n\n"));
}

void roundsplayed()
{
    player1.no_rounds += 1;
    player2.no_rounds += 1;
}

void matchesplayed()
{
    player1.no_matches += 1;
    player2.no_matches += 1;
}
