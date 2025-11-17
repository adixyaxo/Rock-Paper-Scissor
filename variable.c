#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int umove() {
    int u;
    printf("Play your moves\nEnter 1 for rock\nEnter 2 for paper\nEnter 3 for scissor\nEnter 0 to exit game\n\t:");
    scanf("%d", &u);
    return u;
}

int cmove() {
    srand(time(NULL));
    int rno= rand();
    int c = ((rand()) % 3) + 1;
    return c;
}

int match(){
    int user, comp;
    while(1){
        user = umove();
        if(user == 0){
            printf("Exiting the game.....\n");
            break;
        }
        comp = cmove();
        printf("Computer chose: %d\n", comp);
        if(user == comp){
            printf("It's a tie\n");
        }
        else if((user == 1 && comp == 3) || (user == 2 && comp == 1) || (user == 3 && comp == 2)){
            printf("You win\n");
        }
        else{
            printf("Computer win\n");
        }
    }
    return 0;
}