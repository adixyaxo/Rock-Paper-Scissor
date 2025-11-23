#ifndef AUTH_H
#define AUTH_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[50];
    char password[50];
    int high_score;
    int no_matches;
    int no_rounds;
    int wins;
    int losses;
    int ties;
    int score;
} USER;


extern USER user;      // For single player
extern USER player1;   // Multiplayer
extern USER player2;

int verify(char name[], char password[]);
void olduser();
int authenticate();
int newuser();
int newold();
void logout();
void multiusers();
void mlogout();

#endif