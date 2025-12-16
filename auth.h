// auth.h
#ifndef AUTH_H
#define AUTH_H

#include "ui.h"

// Structure for a user
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
    int declared;
} USER;

// Global variables (defined only in auth.c)
extern USER user;      // Single player
extern USER player1;   // Multiplayer player 1
extern USER player2;   // Multiplayer player 2

extern void declare();

// Function declarations
int verify(char name[], char password[]);
void olduser();
int authenticate();
int newuser();
int newold();
void logout();
void multiusers();
void mlogout();

#endif // AUTH_H
