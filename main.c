#include <stdio.h>
#include <stdlib.h>
#include "variable.c"
//#include "game.c"
#include <unistd.h>

int main() {
    declare();
    printf("Welcome to Rock Paper Scissor Game!\n");
    sleep(1);
    int mode = singleormulti();
    if (mode == 0) {
        match();
    } else if (mode == 1) {
        multiplayer();
    }
}

//ERRORS ENCOUNTERED DURING COMPILATION
//There was an error orignated due to the space not left in before scanning the character in the scanf befor %c
//error due to including game.c file in variable.c and main.c both 