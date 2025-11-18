#include <stdio.h>
#include <stdlib.h>
#include "variable.c"
//#include "game.c"
#include "stats.c"

int main() {
    return match();
}

//ERRORS ENCOUNTERED DURING COMPILATION
//In file included from main.c:4:0:
// game.c:4:5: error: redefinition of 'modes'
//  int modes() {
//      ^~~~~
// In file included from variable.c:4:0,
//                  from main.c:3:
// game.c:4:5: note: previous definition of 'modes' was here
//  int modes() {
//      ^~~~~
