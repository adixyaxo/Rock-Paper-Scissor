#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char *name;
    char *password;
    int *score;
}USER;

USER user;


int newold()
{
    int choice;
    printf("Are you a new user or existing user?\nNew User--1\nExisting User--2\nEnter choice (1 or 2): ");
    scanf("%d", &choice);
    if (choice==2)
    {
        return authenticate();
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
    }
    else
    {
        printf("Access Denied\nTry Again\n");
        authenticate();
    }
    return status;
}

int verify(name,password)
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