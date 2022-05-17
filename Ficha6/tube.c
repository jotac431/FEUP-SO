#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define READ_END 0
#define WRITE_END 1
char *cmd1[] = {"ls", "-l", NULL};
char *cmd2[] = {"wc", "-l", NULL};
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Bad format\n");
        exit(EXIT_FAILURE);
    }

    int size = strlen(argv[1]);

    //char *c = argv[1];
    //c = malloc(size);

    //strcat(c, argv[1]);
    
    //printf("%c\n", c[0]);

    char first[2];
    char second[2];
    char third[2];
    char fourth[2];

    strncpy(first, argv[1], 2);

    printf("%s\n", first);

    strncpy(second, argv[1]+3, 2);

    printf("%s\n", second);

    char *cmd3[] = {first, second, NULL};

    strncpy(third, argv[1]+8, 2);

    printf("%s\n", third);

    strncpy(fourth, argv[1]+11, 2);

    printf("%s\n", fourth);

    char *cmd4[] = {third, fourth, NULL};

    int fd[2];
    pid_t pid;
    if (pipe(fd) < 0)
    {
        /* pipe error */
    }
    if ((pid = fork()) < 0)
    {
        /* fork error */
    }
    if (pid > 0)
    {
        close(fd[READ_END]);
        dup2(fd[WRITE_END], STDOUT_FILENO); // stdout to pipe
        close(fd[WRITE_END]);
        // parent writes to the pipe
        if (execvp(cmd1[0], cmd1) < 0)
        {
            /* exec error */
        }
    }
    else
    {
        close(fd[WRITE_END]);
        dup2(fd[READ_END], STDIN_FILENO); // stdin from pipe
        close(fd[READ_END]);
        if (execvp(cmd2[0], cmd2) < 0)
        {
            /* exec error */
        }
    }
}
