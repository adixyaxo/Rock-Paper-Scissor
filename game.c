#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "auth.h"
#include "ui.h"
#include "game.h"

int modes()
{
    int n;
    scanui("Choose one game mode from the following\nSurvival Challenge :: 1\nBest of Series :: 2\nQuick Match :: 3\n", &n);

    if (n == 1)
    {
        return -1;
    }
    else if (n == 2)
    {
        int nr;
        printui("Enter number of rounds (must be odd number): ");
        scanui("%d", &nr);
        return nr;
    }
    else if (n == 3)
    {
        return 1;
    }
    else
    {
        printui("Invalid Choice, Please choose again\n");
        return modes();
    }
}

int singleormulti()
{
    int n;
    scanui("Choose one mode from the following\nPlay with computer :: 1\nPlay with Friend :: 2\n", &n);
    if (n == 1)
    {
        return 0;
    }
    else if (n == 2)
    {
        return 1;
    }
    else
    {
        printui("Invalid Choice, Please choose again\n");
        return singleormulti();
    }
}
