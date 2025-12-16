#include <stdio.h>
#include <stdlib.h>
#include "variable.c"  
#include "ui.h"

int main(int argc, char *argv[])
{
    ui_init(&argc, &argv);

    declare();
    printui("Welcome to Rock Paper Scissor Game!\n");

    int mode = singleormulti();

    if (mode == 0)
        match();

    else
        multiplayer();

    ui_start();
    return 0;
}

//ERRORS ENCOUNTERED DURING COMPILATION
//There was an error orignated due to the space not left in before scanning the character in the scanf befor %c
//error due to including game.c file in variable.c and main.c both 