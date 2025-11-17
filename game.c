#include <stdio.h>
#include <stdlib.h>

int modes() {
    int n,m;
    printf("Choose one game mode from the following\nSurvival Challenge :: 1\nBest of Series :: 2\nQuick Match :: 3\n");
    scanf("%d", &n);
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
        return(modes());
    }
}
int rounds() {
    int r;
    printf("Enter number of rounds you want to play: ");
    scanf("%d", &r);
    return r;
}
