#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
int modes() {
    int n;
    printf("Choose one game mode from the following\nSurvival Challenge :: 1\nBest of Series :: 2\nQuick Match :: 3\n");
    scanf("%d",&n);
    if (n==1)
    {
        return -1;
    }
    else if(n==2)
    {
        int nr;
        printf("Enter number of rounds (must be odd number): ");
        scanf("%d", &nr);
        return nr;
    }
    else if (n==3)
    {
        return 1;
    }
    else
    {
        printf("Invalid Choice, Please choose again\n");
        modes();
    }
}

int difficulty() {
    int n;
    printf("Choose one difficulty level from the following\nHard :: 1\nNormal :: 2\nEasy :: 3\n");
    scanf("%d",&n);
    if (n==1 || n==2 || n==3)
    {
        return n;
    }
    else
    {
        printf("Invalid Choice, Please choose again\n");
        difficulty();
    }
}

