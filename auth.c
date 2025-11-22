#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

USER user;

//prototypes
int verify(char name[], char password[]);
void olduser();
int authenticate();
int newuser();
int newold();
void logout();

// this programme is going to create indivisual txt files with user data and also modify exiting user data files using read write and append modes

void olduser()
{
    FILE *fptr = fopen(user.name, "r");
    if (!fptr)
    {
        printf("Error opening user file.\n");
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
    char name[50];
    char password[50];

    printf("\nEnter Username: ");
    scanf(" %49s", name);
    printf("\nEnter Password: ");
    scanf(" %49s", password);

    int status = verify(name, password);

    if (status == 1)
    {
        printf("Welcome %s\n", name);
        strcpy(user.name, name);
        strcpy(user.password, password);
        olduser();
        return 1;
    }
    else
    {
        printf("Access Denied\nTry Again\n");
        return authenticate();
    }
}

int newuser()
{
    char name[50];
    char password[50];

    printf("\nEnter Username: ");
    scanf(" %49s", name);
    printf("\nEnter Password: ");
    scanf(" %49s", password);

    FILE *fptr = fopen(name, "w");
    if (!fptr)
    {
        printf("Error creating user file.\n");
        return 0;
    }

    fprintf(fptr, "%s\n", name);
    fprintf(fptr, "%s\n", password);
    fprintf(fptr, "0\n"); // high_score
    fprintf(fptr, "0\n"); // no_matches
    fprintf(fptr, "0\n"); // no_rounds
    fprintf(fptr, "0\n"); // wins
    fprintf(fptr, "0\n"); // losses
    fprintf(fptr, "0\n"); // ties
    fclose(fptr);

    printf("User Registered Successfully\n");

    strcpy(user.name, name);
    strcpy(user.password, password);

    return 1;
}

int newold()
{
    int choice;
    printf("Are you a new user or existing user?\nNew User--1\nExisting User--2\nEnter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 2)
    {
        return authenticate();
    }
    else if (choice == 1)
    {
        printf("Registering New User\n");
        return newuser();
    }
    else
    {
        printf("Invalid Choice, Please choose again\n");
        return newold();
    }
}

int verify(char name[], char password[])
{
    FILE *fptr = fopen(name, "r");
    if (fptr == NULL)
    {
        printf("User not found\n");
        return newold();
    }

    char stored_name[50];
    char stored_password[50];

    fgets(stored_name, 50, fptr);
    fgets(stored_password, 50, fptr);

    // Remove newlines
    stored_name[strcspn(stored_name, "\n")] = 0;
    stored_password[strcspn(stored_password, "\n")] = 0;

    fclose(fptr);

    if (strcmp(name, stored_name) == 0 && strcmp(password, stored_password) == 0)
    {
        return 1;
    }
    return 0;
}

void logout()
{
    FILE *fptr = fopen(user.name, "w");
    if (!fptr)
    {
        printf("Error opening user file for logout.\n");
        return;
    }

    fprintf(fptr, "%s\n", user.name);
    fprintf(fptr, "%s\n", user.password);
    fprintf(fptr, "%d\n", user.high_score);
    fprintf(fptr, "%d\n", user.no_matches);
    fprintf(fptr, "%d\n", user.no_rounds);
    fprintf(fptr, "%d\n", user.wins);
    fprintf(fptr, "%d\n", user.losses);
    fprintf(fptr, "%d\n", user.ties);
    fclose(fptr);

    printf("User %s logged out successfully.\n", user.name);
}
