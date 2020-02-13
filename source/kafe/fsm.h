#include <kafe/fsm.h>
#include <kafe/stack.h>

#include <stdio.h>

int fsm_run(FILE *pFile)
{
    Stack s;
    if (stack_init(&s) != 0)
    {
        printf("Couldn't initialize the stack!\n");
        return -1;
    }

    // reading characters from file until end
    for (c = fgetc(pFile); !feof(pFile); c = fgetc(pFile))
    {
        //
    }

    if (stack_free(&s) != 0)
    {
        printf("Couldn't free the stack!\n");
        return -1;
    }

    return 0;
}