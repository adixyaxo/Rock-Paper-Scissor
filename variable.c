#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "stats.h"
#include "ui.h"
#include "variable.h"
#include "auth.h"
#include "game.h"

// imported game to use it in the loop jisse ham pata kar paen ki loop ko kitni bar chalana hai

char umove()
{
    char u;
    scanui_char("\n\n---PLAY YOUR MOVES---\nEnter 1 or R for rock\nEnter 2 or P for paper\nEnter 3 or S for scissor\nEnter M to return to Main Menu\nEnter Q to quit current game\nEnter T to display current stats\nEnter ESC or 27 to exit application\nPlay your move :: ",&u);
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
    newold();
    user.no_matches += 1;
    int rounds, n;
    difficulty();
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
        char user_move;
        int comp;

        user_move = umove();
        comp = cmove();

        // checking for esc
        int usmove = user_move;

        printui(formatui("Computer chose: %d\n", comp));

        if (user_move != '1' && user_move != '2' && user_move != '3' &&
            user_move != 'R' && user_move != 'P' && user_move != 'S' &&
            user_move != 'r' && user_move != 'p' && user_move != 's' &&
            user_move != 'M' && user_move != 'Q' && user_move != 'T' &&
            user_move != 'm' && user_move != 'q' && user_move != 't' &&
            user_move != 27)
        {
            printui("Invalid input \n Please try again\n");
            sleep(1);
            continue;
        }
        else if (usmove == 27) // ESC
        {
            printui("Exiting the game...\n");
            exit(0);
        }
        else if (user_move == 'Q' || user_move == 'q')
        {
            printui("Skipping to next round...\n");
            continue;
        }
        else if (user_move == 'M' || user_move == 'm')
        {
            printui("Returning to Main Menu...\n");
            break;
        }
        else if (user_move == 'T' || user_move == 't')
        {
            displaystats();
            continue;
        }
        else if ((user_move == '1' && comp == 1) ||
                 (user_move == '2' && comp == 2) ||
                 (user_move == '3' && comp == 3) ||
                 ((user_move == 'R' || user_move == 'r') && comp == 1) ||
                 ((user_move == 'P' || user_move == 'p') && comp == 2) ||
                 ((user_move == 'S' || user_move == 's') && comp == 3))
        {
            printui("\nRESULT :: This is a tie\n");
            tie();
            sleep(1);
        }
        else if (
            (user_move == '1' && comp == 3) ||
            (user_move == '2' && comp == 1) ||
            (user_move == '3' && comp == 2) ||
            ((user_move == 'R' || user_move == 'r') && comp == 3) ||
            ((user_move == 'P' || user_move == 'p') && comp == 1) ||
            ((user_move == 'S' || user_move == 's') && comp == 2))
        {
            printui("\nRESULT :: Congratulations You Win\n");
            win();
            sleep(1);
        }
        else
        {
            printui("\nRESULT :: You Lost\n");
            lost();
            sleep(1);
        }
        user.no_rounds += 1;
        highscore();
    }
    logout();
    return 0;
}

int multiplayer()
{
    multiusers();
    int rounds, n;
    difficulty();
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
    matchesplayed();
    for (int i = 0; i < rounds; i += n)
    {
        char p1_move;
        char p2_move;

        printui(formatui(" %s, enter your move: ", player1.name));
        p1_move = umove();
        clearui(); // Clear krdega screen ko taki player 2 ko pata na chale ki player 1 ne kya choose kiya hai
        printui(formatui(" %s, enter your move: ", player2.name));
        p2_move = umove();
        clearui();

        printui(formatui("%s chose: %c\n", player1.name, p1_move));
        printui(formatui("%s chose: %c\n", player2.name, p2_move));
        // checking for esc
        int us1move = p1_move;
        int us2move = p2_move;

        if ((p1_move != '1' && p1_move != '2' && p1_move != '3' &&
             p1_move != 'R' && p1_move != 'P' && p1_move != 'S' &&
             p1_move != 'r' && p1_move != 'p' && p1_move != 's' &&
             p1_move != 'M' && p1_move != 'Q' && p1_move != 'T' &&
             p1_move != 'm' && p1_move != 'q' && p1_move != 't' &&
             p1_move != 27) ||
            (p2_move != '1' && p2_move != '2' && p2_move != '3' &&
             p2_move != 'R' && p2_move != 'P' && p2_move != 'S' &&
             p2_move != 'r' && p2_move != 'p' && p2_move != 's' &&
             p2_move != 'M' && p2_move != 'Q' && p2_move != 'T' &&
             p2_move != 'm' && p2_move != 'q' && p2_move != 't' &&
             p2_move != 27))
        {
            printui("Invalid input \n Please try again\n");
            sleep(1);
            continue;
        }
        else if (us1move == 27 || us2move == 27) // ESC
        {
            printui("Exiting the game...\n");
            exit(0);
        }
        else if (p1_move == 'Q' || p1_move == 'q' ||
                 p2_move == 'Q' || p2_move == 'q')
        {
            printui("Skipping to next round...\n");
            continue;
        }
        else if (p1_move == 'M' || p1_move == 'm' ||
                 p2_move == 'M' || p2_move == 'm')
        {
            printui("Returning to Main Menu...\n");
            break;
        }
        else if (p1_move == 'T' || p1_move == 't' ||
                 p2_move == 'T' || p2_move == 't')
        {
            mdisplaystats();
            continue;
        }
        else if ((p1_move == '1' && p2_move == '1') ||
                 (p1_move == '2' && p2_move == '2') ||
                 (p1_move == '3' && p2_move == '3') ||
                 ((p1_move == 'R' || p1_move == 'r') && p2_move == '1') ||
                 ((p1_move == 'P' || p1_move == 'p') && p2_move == '2') ||
                 ((p1_move == 'S' || p1_move == 's') && p2_move == '3'))
        {
            printui("\nRESULT :: This is a tie\n");
            mtie(difficulty_level);
            sleep(1);
            roundsplayed();
        }
        else if (
            (p1_move == '1' && p2_move == '3') ||
            (p1_move == '2' && p2_move == '1') ||
            (p1_move == '3' && p2_move == '2') ||
            ((p1_move == 'R' || p1_move == 'r') && p2_move == '3') ||
            ((p1_move == 'P' || p1_move == 'p') && p2_move == '1') ||
            ((p1_move == 'S' || p1_move == 's') && p2_move == '2'))
        {
            printui("\nRESULT :: Player 1 Wins\n");
            mp1win(difficulty_level);
            sleep(1);
            roundsplayed();
        }
        else
        {
            printui("\nRESULT :: Player 2 Wins\n");
            mp2win(difficulty_level);
            sleep(1);
            roundsplayed();
        }
    }
    
    return 0;
}
