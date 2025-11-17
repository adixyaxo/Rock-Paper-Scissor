#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int umove() {
    int u;
    printf("Play your moves\nEnter 1 for rock\nEnter 2 for paper\nEnter 3 for scissor\nEnter 0 to exit game\n\t:");
    scanf("%d", &u);
    return u;
}

int cmove() {
    srand(time(NULL));
    int rno= rand();
    int c = ((rand()) % 3) + 1;
    return c;
}

int main()
{
    printf("%d",cmove());
    printf("%d",cmove());
    printf("%d",cmove());
    printf("%d",cmove());
    printf("%d",cmove());
    return 0;
}