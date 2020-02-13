#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *pFile;
    char c = 0;

    // getting filename to test
    char *filename = (char*) malloc(sizeof(char) * 128);
    if (argc == 2)
        strcpy(filename, argv[1]);
    else
        strcpy(filename, "tests/first.txt");

    if (pFile = fopen(filename, "rt"))
    {
        for (c = fgetc(pFile); !feof(pFile); c = fgetc(pFile))
        {
            printf("%c", c);
        }
        fclose(pFile);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}