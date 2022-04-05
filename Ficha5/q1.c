#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    /* fork a child process */
    printf("%d\n", getpid());
    if (fork() == 0)
    {
        printf("%d\n", getpid());
        //kill(getpid(), SIGSEGV);
    }
    /* fork another child process */
    if (fork() == 0)
    {
        printf("%d\n", getpid());
        //kill(getpid(), SIGSEGV);
    }
    /* and fork another */
    if (fork() == 0)
    {
        printf("%d\n", getpid());
        //kill(getpid(), SIGSEGV);
    }
    return EXIT_SUCCESS;
}