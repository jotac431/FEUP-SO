#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    printf("%d\n", getpid());
    for (int i = 0; i < 4; i++)
        if (fork() == 0)
        {
            printf("%d\n", getpid());
        }
    return EXIT_SUCCESS;
}
