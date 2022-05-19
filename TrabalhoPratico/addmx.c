#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("usage: addmx file1 file2 \n");
        exit(EXIT_FAILURE);
    }

    FILE *infile1 = fopen(argv[1], "r");
    FILE *infile2 = fopen(argv[2], "r");

    if (infile1 == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int lin1, col1, lin2, col2;
    char ch;

    fscanf (infile1, "%dx%d\n", &lin1, &col1);
    fscanf (infile2, "%dx%d\n", &lin2, &col2);

    if (lin1 != lin2 || col1 != col2){
        
        perror("Matrix dimensions do not match");
        exit(EXIT_FAILURE);
    }
    
    int *matrix1 = mmap(NULL, lin1 * col1 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    int *matrix2 = mmap(NULL, lin1 * col1 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    int *matrix_res = mmap(NULL, lin1 * col1 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

    int v;
    int i = 0;
    while (fscanf(infile1, "%d ", &v) == 1){
        matrix1[i] = v;
        i++;
    }
    fclose(infile1);

    i = 0;
    while (fscanf(infile2, "%d ", &v) == 1){
        matrix2[i] = v;
        i++;
    }
    fclose(infile2);

    i = 0;
    while(i < lin1 * col1){
        matrix_res[i] = 0;
        i++;
    }


    //calculate matrix
    for (int i = 0; i < col1; i++){
        pid_t pid = fork();
        

        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            for (int r = 0; r < lin1; r++)
            {
                matrix_res[r * col1 + i]  = matrix1[r * col1 + i] + matrix2[r * col1 + i];
            }
            exit(EXIT_SUCCESS);
        }
    }

    
    //wait for all childs
    for (i = 0; i < col1; i++)
	{
		if (waitpid(-1, NULL, 0) < 0)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}

    printf("%dx%d\n", lin1, col1);
    for (int r = 0; r < lin1; r++)
    {
        for(int c = 0; c < col1; c++)
        {
            printf("%d ", matrix_res[r * col1 + c]);
        }
        printf("\n");
    }
    
    //released shared memory
    if (munmap(matrix1, sizeof(matrix1)) < 0)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
        if (munmap(matrix2, sizeof(matrix2)) < 0)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}
        if (munmap(matrix_res, sizeof(matrix_res)) < 0)
	{
		perror("munmap");
		exit(EXIT_FAILURE);
	}

    return 0;
}