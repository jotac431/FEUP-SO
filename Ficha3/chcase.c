#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc > 2 && argc < 1 && (argc == 2 && (argv[1] != "-u" && argv[1] != "-l")))
    {
        printf("Invalid arguments\n");
        return 1;
    }

    FILE *fp;
    char buffer[100];
    char ch;

    switch (argc)
    {
    case 1:
        fp = fopen(argv[1], "r");
        fread(buffer, 1, sizeof(buffer), fp);
        printf("%s\n", buffer);
        fclose(fp);

        return EXIT_SUCCESS;

    case 2:
        if (argv[1] == "-u")
        {
            fp = fopen(argv[1], "r");
            fread(buffer, 1, sizeof(buffer), fp);
            for (int i = 0; i < sizeof(buffer); i++)
            {
                ch = buffer[i];
                putchar(toupper(ch));
            }

            printf("%s\n", buffer);
            fclose(fp);

            return EXIT_SUCCESS;
        }

        fp = fopen(argv[1], "r");
        fread(buffer, 1, sizeof(buffer), fp);
        for (int i = 0; i < sizeof(buffer); i++)
        {
            ch = buffer[i];
            putchar(tolower(ch));
        }

        printf("%s\n", buffer);
        fclose(fp);

        return EXIT_SUCCESS;
    }
}