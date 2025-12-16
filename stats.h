#ifndef STATS_H
#define STATS_H

int difficulty();
void win();
void lost();
void tie();
void highscore();
void displaystats();

void mp1win(int level);
void mp2win(int level);
void mtie();
void mdisplaystats();
void roundsplayed();
void matchesplayed();

extern int difficulty_level;
#endif
