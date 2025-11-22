#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char *name;
    char *password;
    int *high_score;
    int *no_matches;
    int *no_rounds;
    int *wins;
    int *losses;
    int *ties;
    int *score;
}USER;

USER user;

//this programme is going to create indivisual txt files with user data and also modify exiting user data files using read write and append modes
/*

LINE DATA
1 :: USERNAME
2 :: PASSWORD
3 :: GAMES PLAYED
4 :: ROUNDS PLAYED
5 :: WINS
6 :: LOSSES
7 :: TIES
8 :: SCORE

*/

int newold()
{
    int choice;
    printf("Are you a new user or existing user?\nNew User--1\nExisting User--2\nEnter choice (1 or 2): ");
    scanf("%d", &choice);
    if (choice==2)
    {
        authenticate();
    }
    else if (choice==1)
    {
        printf("Registering New User\n");
        return newuser();
    }
    else
    {
        printf("Invalid Choice, Please choose again\n");
        newold();
    }
}


int newuser()
{
    char name[50];
    char password[50];
    printf("\nEnter Username: ");
    scanf(" %s", name);
    printf("\nEnter Password: ");
    scanf(" %s", password);
    FILE *fptr = fopen(name,"w");
    fprintf(fptr, "%s\n", name);
    fprintf(fptr, "%s\n", password);
    fprintf(fptr, "0\n"); //high_score
    fprintf(fptr, "0\n"); //no_matches
    fprintf(fptr, "0\n"); //no_rounds
    fprintf(fptr, "0\n"); //wins
    fprintf(fptr, "0\n"); //losses
    fprintf(fptr, "0\n"); //ties
    fclose(fptr);
    printf("User Registered Successfully\n");
    user.name = name;
    user.password = password;
    return 1;
}


int authenticate()
{
    char name[50];
    char password[50];
    printf("\nEnter Username: ");
    scanf(" %s", name);
    printf("\nEnter Password: ");
    scanf(" %s", password);
    int status = verify(name, password);
    if (status == 1)
    {
        printf("Welcome %s\n", name);
        user.name = name;
        user.password = password;
        olduser();
        return 1;
    }
    else
    {
        printf("Access Denied\nTry Again\n");
        authenticate();
        return 0;
    }
}

int verify(char name[],char password[])
{
    FILE *fptr = fopen(name,"r");
    if (fptr == NULL)
    {
        int choice;
        printf("User not found\n");
        return newold();
    }
    char stored_name[50];
    char stored_password[50];
    fgets(stored_name,50,fptr);
    fgets(stored_password,50,fptr);
    if (strcmp(name,stored_name)==0 && strcmp(password,stored_password)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    fclose(fptr);
}

void olduser()
{
    // user ka existing data load krne ke liye to show realtime results
    FILE *fptr = fopen(user.name,"r");
    char line[50];
    for (int i = 0; i < 8; i++)
    {
        fgets(line,50,fptr);
        switch(i)
        {
            //learned that atoi converts string to int
            case 3:
                user.high_score = atoi(line);
                break;
            case 4:
                user.no_matches = atoi(line);
                break;
            case 5:
                user.no_rounds = atoi(line);
                break;
            case 6:
                user.wins = atoi(line);
                break;
            case 7:
                user.losses = atoi(line);
                break;
            case 8:
                user.ties = atoi(line);
                break;
        }
    }
    fclose(fptr);
}


void logout()
{
    user.name = NULL;
    user.password = NULL;
    printf("Logged out successfully\n");
}