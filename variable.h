// variable.h
#ifndef VARIABLE_H
#define VARIABLE_H

#include "auth.h"   // AI: reuse USER instead of redefining Player

extern int difficulty_level;

// function declarations (AI: added to avoid implicit declaration)
int match();
int multiplayer();

#endif
