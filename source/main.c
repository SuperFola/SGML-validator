#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <kafe/fsm.h>

int main(int argc, char **argv)
{
    FILE *pFile;

    // getting filename to test
    char *filename = (char*) malloc(sizeof(char) * 128);
    if (argc == 2)
        strcpy(filename, argv[1]);
    else
        strcpy(filename, "tests/first.txt");

    if (pFile = fopen(filename, "rt"))
    {
        fsm_run(pFile);
        fclose(pFile);
    }
    else
    {
        printf("Couldn't open file %s\n", filename);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}