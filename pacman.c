/* This is rob```'s pacman */
#include <unistd.h>
#include <stdio.h>

#define N 8

int main(void)
{
    int i, k = 3, x = 99;

    while (k --> 0)
    {
        for (i = 0; i < N; i++)
            printf("%.*s o", !i, " ");
        printf("\r%c[1;%dm", 27, 33);
        for (i = 0; i < (N<<2); i++)
        {
            printf("%*s%c\r", i/2 + 1, "", x & ~(!(i % 2) << 5));
            fflush(stdout);
            usleep(100000);
        }
        printf("\r%c[0m", 27);
    }
    return 0;
}
