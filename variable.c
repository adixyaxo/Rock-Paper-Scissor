#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "game.c"
#include "stats.c"
#include <unistd.h>
// imported game to use it in the loop jisse ham pata kar paen ki loop ko kitni bar chalana hai

char umove()
{
    char u;
    printf("\n\nPlay your moves\nEnter 1 or R for rock\nEnter 2 or P for paper\nEnter 3 or S for scissor\nEnter M to return to Main Menu\nEnter Q to quit current game\nEnter T to display current stats\nEnter ESC to exit application\nPlay your move :: ");
    scanf(" %c", &u);
    sleep(1);
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
    user.no_matches += 1;
    int rounds, n;
    int mode = modes();
    if (mode == 1)
    {
        rounds = 1;
        n = 1;
    }
    else if (mode == -1)
    {
        rounds = 1;
        n = 0;
    }
    else
    {
        rounds = mode;
        n = 1;
    }
    for (int i = 0; i < rounds; i += n)
    {
        int user, comp;
        user = umove();
        comp = cmove();
        printf("Computer chose: %d\n", comp);

        if (user != '1' && user != '2' && user != '3' &&
            user != 'R' && user != 'P' && user != 'S' &&
            user != 'r' && user != 'p' && user != 's' &&
            user != 'M' && user != 'Q' && user != 'T' &&
            user != 'm' && user != 'q' && user != 't' &&
            user != 27)
        {
            printf("Invalid input \n Please try again\n");
            sleep(1);
            continue;
            // agar user kuch aur input krta hai jo nahi hai options me to repeat ho jaega loop
        }
        else if (user == 27)
        {
            printf("Exiting the game...\n");
            exit(0);
            // learned about exit function also about the asscii value of esc key
        }
        else if (user == 'Q' || user == 'q')
        {
            printf("Skipping to next round...\n");
            continue;
            // loop ko continue kreaga aur ye game skip ho kr next game chal jaega
        }
        else if (user == 'M' || user == 'm')
        {
            printf("Returning to Main Menu...\n");
            break;
            // ye pura while loop se bahar nikal jaega aur main menu pr chala jaega
        }
        else if (user == 'T' || user == 't')
        {
            displaystats();
            continue;
        }
        else if (user == comp)
        {
            printf("\nThis is a tie\n");
            p1.ties += 1;
            sleep(2);
            // tie condition
        }
        else if ((user == '1' && comp == 3) || (user == '2' && comp == 1) || (user == '3' && comp == 2) || ((user == 'R' || user == 'r') && comp == 3) || ((user == 'P' || user == 'p') && comp == 1) || ((user == 'S' || user == 's') && comp == 2))
        {
            printf("\nCongratulations You Win\n");
            p1.wins += 1;
            sleep(2);
            // user win condition
            // yahan par hamne ascii values ka use nahi kra cause char apne aap convert hore the
        }
        else
        {
            printf("\nYou Lost\n"); 
            p1.losses+=1;
            sleep(2);
            // user lose condition
        }
        p1.roundsplayed += 1; // last me lagaya hai taki round khelne ke baad hi round count regester ho
    }
}