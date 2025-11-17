#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int umove() {
    int p;
    printf("Play your moves\nEnter 1 for rock\nEnter 2 for paper\nEnter 3 for scissor\nEnter 0 to exit game\n\t:");
    scanf("%d", &p);
    int t = time(NULL);
    int c = ((rand() * t) % 3) + 1;
    return 0;
}

int cmove() {
    srand(time(NULL));
    int rno= rand();
    printf(rand());
    int c = ((rand()) % 3) + 1;
    return c;
}

int main()
{
    printf("%d,cmove()");
}