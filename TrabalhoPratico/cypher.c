#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define LINESIZE 256
#define READ_END 0
#define WRITE_END 1

/* assistant function that reads from cypher.txt and saves the words in words */
int ler(char words[26][25])
{
    struct stat sb2;
    if (stat("cypher.txt", &sb2) == -1)
    {
        perror("stat");
        return -1;
    }
    FILE *file = fopen("cypher.txt", "r");
    if (!file)
        return -1;
    char lines[sb2.st_size];
    fread(lines, sb2.st_size, 1, file);
    fclose(file);
    int k = 0;
    int s = 0;
    for (int i = 0; i < sb2.st_size; i++)
    {
        char c = lines[i];
        if (isalpha(c) != 0)
        {
            words[s][k] = c;
            k++;
        }
        else
        {
            words[s][k] = '\0';
            s++;
            k = 0;
        }
        if (k != 0)
            words[s][k] = '\0';
    }
    return s;
}
/* assistant function that checks if the given word is one of the ones to be changed */
int is(char *word, char words[26][25], int y)
{
    int i;
    for (i = 0; i <= y; i++)
    {
        if (strcmp(word, words[i]) == 0)
        {
            break;
        }
    }
    if (i == y + 1)
        return -1;
    if (i % 2 == 0)
        return i + 1;
    return i - 1;
}
/* main funtion */
int main(int argc, char *argv[])
{
    int nbytes, n, fd[2], p2[2];
    pid_t pid;

    struct stat sb;
    if (stat(argv[1], &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    char line[sb.st_size];
    char lines[sb.st_size];
    if (pipe(fd) < 0)
    {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }
    if (pipe(p2) < 0)
    {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }
    if ((pid = fork()) < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        /* parent */
        /* write to pipe fd */
        close(fd[READ_END]);
        FILE *file = fopen(argv[1], "r");
        if (!file)
            exit(EXIT_FAILURE);
        char line[sb.st_size];
        fread(line, sb.st_size, 1, file);
        fclose(file);
        if (write(fd[WRITE_END], line, sizeof(line)) < 0)
        {
            fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
        }
        close(fd[WRITE_END]);
        /* wait for child */
        if (waitpid(pid, NULL, 0) < 0)
        {
            fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
        }
        /* read from pipe p2 */
        close(p2[WRITE_END]);
        if ((n = read(p2[READ_END], lines, sizeof(lines))) < 0)
        {
            fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
        }
        close(p2[READ_END]);
        /* write in file */
        FILE *file1 = fopen(argv[2], "w");
        if (!file1)
            exit(EXIT_FAILURE);
        fwrite(lines, n, 1, file1);
        /* exit parent */
        exit(EXIT_SUCCESS);
    }
    else
    {
        /* child */
        /* read from pipe fd */
        close(fd[WRITE_END]);
        if ((nbytes = read(fd[READ_END], line, sb.st_size)) < 0)
        {
            fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
        }
        close(fd[READ_END]);
        /* read from file */
        char words[26][25];
        int y;
        if ((y = ler(words)) == -1)
            exit(EXIT_FAILURE);
        /* replace the words */
        int k = 0;
        int w = 0;
        char word[25];
        memset(word, 0, 25);
        for (int i = 0; i < nbytes; i++)
        {
            char c = line[i];
            if (isalpha(c) != 0)
            {
                word[k] = c;
                k++;
            }
            else
            {
                if (k != 0)
                {
                    int s = is(word, words, y);
                    if (s != -1)
                    {
                        strcpy(word, words[s]);
                    }
                    int z = strlen(word);
                    for (int j = 0; j < z; j++)
                    {
                        char d = word[j];
                        lines[w] = d;
                        w++;
                    }
                }
                lines[w] = c;
                w++;
                memset(word, 0, 25);
                k = 0;
            }
        }
        if (k != 0)
        {
            int s = is(word, words, y);
            if (s != -1)
            {
                strcpy(word, words[s]);
            }
            int z = strlen(word);
            for (int j = 0; j < z; j++)
            {
                char d = word[j];
                lines[w] = d;
                w++;
            }
            lines[w] = '\0';
        }
        /* write in pipe p2 */
        close(p2[READ_END]);
        if ((write(p2[WRITE_END], lines, strlen(lines))) < 0)
        {
            fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
        }
        close(p2[WRITE_END]);
        /* exit child */
        exit(EXIT_SUCCESS);
    }
}