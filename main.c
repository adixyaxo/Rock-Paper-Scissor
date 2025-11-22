#include <stdio.h>
#include <stdlib.h>
#include "variable.c"
//#include "game.c"
#include <unistd.h>

int main() {
    return match();
}

//ERRORS ENCOUNTERED DURING COMPILATION
//There was an error orignated due to the space not left in before scanning the character in the scanf befor %c
//error due to including game.c file in variable.c and main.c both 