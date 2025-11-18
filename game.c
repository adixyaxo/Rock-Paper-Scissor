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
        modes();
    }
}


//ERRORS ENCOUNTERED DURING COMPILATION
//In file included from main.c:4:0:
// game.c:4:5: error: redefinition of 'modes'
//  int modes() {
//      ^~~~~
// In file included from variable.c:4:0,
//                  from main.c:3:
// game.c:4:5: note: previous definition of 'modes' was here
//  int modes() {
//      ^~~~~
