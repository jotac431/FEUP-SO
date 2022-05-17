#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

void count_phrases(char *filename, int lflag)
{

    FILE *infile = fopen(filename, "r");
    int count = 1;
    char ch;
    char punctuation = ' '; // saves the last processed char, used to check if a sentence has ended

    if (infile == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    if (fgetc(infile) == EOF)
    { // deals with txt files with no text
        printf("0 \n");
        fclose(infile);
        exit(0);
    }

    if (lflag == 1)
    {
        printf("[%i] ", count);
    }
    count++;

    rewind(infile); // resets pointer from previous fgetc

    while ((ch = fgetc(infile)) != EOF)
    {

        if (ch == '\n')
        {
            if (lflag == 1)
            {
                printf(" ");
            }
            continue;
        }

        if (punctuation != '.' && punctuation != '?' && punctuation != '!')
        {
            if (lflag == 1)
            {
                printf("%c", ch);
            }
        }
        else
        {
            if (lflag == 1)
            {
                printf("\n");
                printf("[%i] ", count);
            }

            if (ch != ' ')
            {
                if (lflag == 1)
                {
                    printf("%c", ch);
                }
            }
            count++;
        }
        punctuation = ch;
    }

    if (lflag == 0)
    {
        printf("%i", count - 1);
    }
    fclose(infile);
}

int main(int argc, char *argv[])
{

    int lflag = 0; // 1 if "-l" was used in terminal, 0 if not
    int i = 1;

    if (argc != 2 && argc != 3)
    {
        printf("Correct usage: phrases [-l] file \n");
        exit(1);
    }

    if (strcmp(argv[1], "-l") == 0)
    {
        lflag = 1;
        i = 2;
    }

    count_phrases(argv[i], lflag);
    printf("\n");

    return 0;
}