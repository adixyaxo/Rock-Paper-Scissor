#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "variable.h"
#include "ui.h"
#include "auth.h"
#include "game.h"

// Function to start the game after GTK window is ready
gboolean start_game(gpointer data)
{
    declare(); // Initialize variables or players
    printui("Welcome to Rock Paper Scissor Game!\n");

    int mode = singleormulti(); // Choose game mode

    if (mode == 0)
        match();       // Single player mode
    else
        multiplayer(); // Multiplayer mode

    return FALSE; // Stop the timeout, run only once
}

int main(int argc, char **argv)
{
    // Initialize GTK and setup UI
    ui_init(&argc, &argv);

    // Schedule start_game to run after GTK window is ready
    g_timeout_add(100, start_game, NULL);

    // Enter GTK main loop
    ui_start();
    mlogout();
    return 0;
}



//ERRORS ENCOUNTERED DURING COMPILATION
//There was an error orignated due to the space not left in before scanning the character in the scanf befor %c
//error due to including game.c file in variable.c and main.c both 

/*
gcc `pkg-config --cflags gtk+-3.0` \
auth.c game.c stats.c variable.c ui.c main.c \
-o main `pkg-config --libs gtk+-3.0`


*/