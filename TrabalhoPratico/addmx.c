#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("usage: addmx file1 file2 \n");
        exit(1);
    }

    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    int lin, col;
    char ch;

    fscanf (infile, "%dx%d\n", &lin, &col);
    printf("%d\n", lin);
    printf("%d\n", col);
    printf("%c\n", fgetc(infile));
    
    int *ptr = mmap(NULL, lin * col * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);


    //IMPORTANTE PARA LER MATRIZ
    /*char buf[100];
    while (fscanf(ptr, "%*s %*s %s ",
                  buf)
           == 1)
        printf("%s\n", buf);
    
    */






    /*char *value1;
    while (ch != 'x') {
        ch = fgetc(infile);
        value1 += ch;
        printf("%c\n", ch);
    }
    lin = atoi(value1);
    printf(value1);
    printf("%d\n", lin);

    char *value2;
    while (ch != '\n') {
        ch = fgetc(infile);
        value2 += ch;
    }
    col = atoi(value2);
    printf(value2);
    printf("%d\n", col);
    */
    // FILE *infile2 = fopen(argv[2], "r");

    /*
    if(strcmp(argv[1], "-l")==0){
        lflag = 1;
        i= 2;
    }

    count_phrases(argv[i], lflag);
    printf("\n");
    */
    /*int N = 5;
    int *ptr = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    if (ptr == MAP_FAILED)
    {
        printf("Mapping Failed\n");
        return 1;
    }*/
    return 0;
}