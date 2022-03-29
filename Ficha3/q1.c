#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR_SIZE 64

int main(int argc, char *argv[])
{
    char *p1 = (char *)malloc(MAX_STR_SIZE * sizeof(char));
    char *p2 = (char *)malloc(MAX_STR_SIZE * sizeof(char));
    int result = strcmp(argv[1], argv[2]);
    printf("%d\n", result);
    if (!result)
        printf("the strings are the same\n");
    else if (result < 0)
        printf("%s < %s\n", argv[1], argv[2]);
    else
        printf("%s > %s\n", argv[1], argv[2]);
    strcpy(p1, argv[1]);
    strcpy(p2, argv[2]);
    printf("p1 holds:%s\n", p1);
    printf("p2 holds:%s\n", p2);
    strcat(p1, p2);
    printf("p1 holds:%s\n", p1);
    strcat(p2, p1);
    printf("p2 holds:%s\n", p2);

    //to lowercase
    printf("p1 lower:");
    for (size_t i = 0; i < strlen(p1); ++i)
    {
        printf("%c", tolower(p1[i]));
    }
    printf("\n");
    printf("p2 lower:");
    for (size_t i = 0; i < strlen(p2); ++i)
    {
        printf("%c", tolower(p2[i]));
    }
    printf("\n");

    //ocurrence of 1º string in 2º string
    if(strstr(argv[2], argv[1])){
        //ocurrence number of 1º string in 2º string to do...
        printf("p1 occurs in p2\n");
    }else
        printf("p1 do not occurs in p2\n");

    return EXIT_SUCCESS;
}