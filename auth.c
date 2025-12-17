#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "ui.h"

// Global variables (defined only here)
USER user;    // Single player
USER player1; // Multiplayer player 1
USER player2; // Multiplayer player 2

void declare()
{
    user.declared = 1;
    player1.declared = 1;
    player2.declared = 1;
}

void olduser()
{
    FILE *fptr = fopen(user.name, "r");
    if (!fptr)
    {
        printui("Error opening user file.\n");
        return;
    }

    char line[50];
    for (int i = 0; i < 8; i++)
    {
        if (fgets(line, 50, fptr) == NULL)
            break;

        switch (i)
        {
        case 2:
            user.high_score = atoi(line);
            break;
        case 3:
            user.no_matches = atoi(line);
            break;
        case 4:
            user.no_rounds = atoi(line);
            break;
        case 5:
            user.wins = atoi(line);
            break;
        case 6:
            user.losses = atoi(line);
            break;
        case 7:
            user.ties = atoi(line);
            break;
        }
    }
    fclose(fptr);
}

int authenticate()
{
    char name[50], password[50];


    scanui_str("\nEnter Username: ", name , sizeof(name));
    scanui_str("\nEnter Password: ", password , sizeof(password));

    int status = verify(name, password);

    if (status == 1)
    {
        printui(formatui("Welcome %s\n", name));
        strcpy(user.name, name);
        strcpy(user.password, password);
        olduser();
        return 1;
    }
    else
    {
        printui("Access Denied\nTry Again\n");
        return authenticate();
    }
}

int newuser()
{
    char name[50], password[50];

    scanui_str("\nEnter Username: ", name , sizeof(name));
    scanui_str("\nEnter Password: ", password , sizeof(name));

    FILE *fptr = fopen(name, "w");
    if (!fptr)
    {
        printui("Error creating user file.\n");
        return 0;
    }

    fprintf(fptr, "%s\n%s\n0\n0\n0\n0\n0\n0\n", name, password);
    fclose(fptr);

    printui("User Registered Successfully\n");

    strcpy(user.name, name);
    strcpy(user.password, password);

    return 1;
}

int newold()
{
    int choice;
    scanui_int("Are you a new user or existing user?\nNew User--1\nExisting User--2\nEnter choice (1 or 2): ", &choice);

    if (choice == 2)
        return authenticate();
    else if (choice == 1)
        return newuser();
    else
    {
        printui("Invalid Choice, Please choose again\n");
        return newold();
    }
}

int verify(char name[], char password[])
{
    FILE *fptr = fopen(name, "r");
    if (!fptr)
    {
        printui("User not found\n");
        return newold();
    }

    char stored_name[50], stored_password[50];
    fgets(stored_name, 50, fptr);
    fgets(stored_password, 50, fptr);

    stored_name[strcspn(stored_name, "\n")] = 0;
    stored_password[strcspn(stored_password, "\n")] = 0;

    fclose(fptr);

    return (strcmp(name, stored_name) == 0 && strcmp(password, stored_password) == 0) ? 1 : 0;
}

void logout()
{
    FILE *fptr = fopen(user.name, "w");
    if (!fptr)
    {
        printui("Error opening user file for logout.\n");
        return;
    }

    fprintf(fptr, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n",
            user.name, user.password, user.high_score, user.no_matches, user.no_rounds, user.wins, user.losses, user.ties);

    fclose(fptr);
    printui(formatui("User %s logged out successfully.\n", user.name));
}

void multiusers()
{
    scanui_str("Player 1, please enter your name: ",player1.name , sizeof(player1.name));
    scanui_str("Player 2, please enter your name: ",player2.name , sizeof(player2.name));

}

void mlogout()
{
    char filename[100];
        // AI FIX: limit string length to avoid snprintf truncation
    snprintf(
        filename,
        sizeof(filename),
        "%.45svs%.45s",
        player1.name,
        player2.name
    );


    FILE *fptr = fopen(filename, "w");
    if (!fptr)
    {
        printui("Error opening users file for logout.\n");
        return;
    }

    fprintf(fptr, "NO OF MATCHES :: %d\nNO OF ROUNDS :: %d\n", player1.no_matches, player1.no_rounds);
    fprintf(fptr, "----player 1 stats----\nNAME :: %s\nHIGHSCORE:: %d\nWINS :: %d\nLOSSES :: %d\nTIES :: %d\nSCORE :: %d\n",
            player1.name, player1.high_score, player1.wins, player1.losses, player1.ties, player1.score);
    fprintf(fptr, "----player 2 stats----\nNAME :: %s\nHIGHSCORE:: %d\nWINS :: %d\nLOSSES :: %d\nTIES :: %d\nSCORE :: %d\n",
            player2.name, player2.high_score, player2.wins, player2.losses, player2.ties, player2.score);

    fclose(fptr);
}
