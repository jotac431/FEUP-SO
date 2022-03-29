#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE * fp;

    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");
        fseek(fp, 0, SEEK_END);
        fseek(fp, 0, 0);
        char buffer[20];
        fread(buffer, 1, sizeof(buffer), fp);
        printf("%s\n", buffer);
        fclose(fp);
    }
    
    return EXIT_SUCCESS;
}