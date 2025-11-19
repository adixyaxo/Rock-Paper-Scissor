#include <stdio.h>
#include <stdlib.h>
#include "variable.c"
//#include "game.c"
#include "stats.c"

int main() {
    reset();
    return match();
}

//ERRORS ENCOUNTERED DURING COMPILATION
//There was an error orignated due to the space not left in before scanning the character in the scanf befor %c
