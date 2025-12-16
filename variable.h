// variable.h
#ifndef VARIABLE_H
#define VARIABLE_H

typedef struct {
    char name[50];
    char password[50];
    int high_score;
    int no_matches;
    int no_rounds;
    int wins;
    int losses;
    int ties;
    int score;
} Player;

extern Player player1;
extern Player player2;

extern int difficulty_level;

#endif
