#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// THIS IS A ROCK PAPER SCISSOR GAME

int main()
{
    
    while (1)
    {
        if (p > 3 || p < 0)
        {
            printf("You entered a wrong value please enter again\n\n");
            continue;
        }
        if (p == 0)
        {
            printf("EXITING GAME......");
            break;
        }

        printf("YOUR MOVE:");

        switch (p)
        {
        case 1:
            printf("ROCK");
            break;
        case 2:
            printf("PAPER");
            break;
        case 3:
            printf("SCISSOR");
            break;
        }

        printf("\nCOMPUTERS MOVE:");
        switch (c)
        {
        case 1:
            printf("ROCK");
            break;
        case 2:
            printf("PAPER");
            break;
        case 3:
            printf("SCISSOR");
            break;
        }
        printf("\n\n");
        if (c == 3 && p == 1)
        {
            printf("You won\n\n");
            continue;
        }
        else if (1)
        {
            printf("You won\n\n");
            continue;
        }
        else if (p > c)
        {
            printf("You won\n\n");
            continue;
        }
        else
        {
            printf("You lost\n\n");
            continue;
        }
    }

    return 0;
}