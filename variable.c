#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.c"
// imported game to use it in the loop jisse ham pata kar paen ki loop ko kitni bar chalana hai

char umove()
{
    char u;
    printf("\n\nPlay your moves\nEnter 1 or R for rock\nEnter 2 or P for paper\nEnter 3 or S for scissor\nEnter M to return to Main Menu\nEnter Q to quit current game\nEnter T to display current stats\nEnter ESC to exit application\nPlay your move :: ");
    scanf(" %c",&u);
    return u;
}

int cmove()
{
    srand(time(NULL));
    // ye line random number ko time ke hisab se seed krke generate krne k liye hoti hai
    int rno = rand();
    int c = ((rno) % 3) + 1;
    // ye line 1 se 3 tak random number generate krne k liye hoti hai
    return c;
}

int match()
{
    int rounds,n;
    int mode=modes();
    if (mode==1)
    {
        rounds=1;
        n=1;
    }
    else if (mode==-1)
    {
        rounds=1;
        n=0;
    }
    else
    {
        rounds=mode;
        n=1;
    }
    for (int i = 0; i < rounds; i+=n)
    {
        int user, comp;
        user = umove();
        comp = cmove();
        printf("Computer chose: %d\n", comp);
        if (user == 27)
        {
            exit(0);
            // learned about exit function also about the asscii value of esc key
        }
        else if (user == 'Q' || user == 'q')
        {
            continue;
            // loop ko continue kreaga aur ye game skip ho kr next game chal jaega
        }
        else if (user == 'M' || user == 'm')
        {
            break;
            // ye pura while loop se bahar nikal jaega aur main menu pr chala jaega
        }
        else if (user == 'T' || user == 't')
        {
            // will add the stats soon
            continue;
        }
        else if (user == comp)
        {
            printf("This is a tie\n");
            // tie condition
        }
        else if ((user == 1 && comp == 3) || (user == 2 && comp == 1) || (user == 3 && comp == 2) || (user == 'R' && comp == 3) || (user == 'P' && comp == 1) || (user == 'S' && comp == 2))
        {
            printf("You Win\n");
            // user win condition
            // yahan par hamne ascii values ka use nahi kra cause char apne aap convert hore the
        }
        else
        {
            printf("You Lost\n");
            // user lose condition
        }
    }
}