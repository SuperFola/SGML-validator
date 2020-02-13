#include <kafe/fsm.h>
#include <kafe/stack.h>

#include <stdio.h>

int fsm_run(FILE *pFile)
{
    Stack stack;
    if (stack_init(&stack) != 0)
    {
        printf("Couldn't initialize the stack!\n");
        return -1;
    }

    State s;

    // reading characters from file until end
    for (c = fgetc(pFile); !feof(pFile); c = fgetc(pFile))
    {
        switch (s.state)
        {
            case s.Start:
                break;
            
            case s.TagStart:
                break;
            
            case s.TagNameFeed:
                break;
            
            case s.TagNameEnd:
                break;
            
            case s.TagAttr:
                break;
            
            case s.TagEnd:
                break;
            
            case s.ClosingTagStart:
                break;

            default:
                break;
        }
    }

    if (stack_free(&stack) != 0)
    {
        printf("Couldn't free the stack!\n");
        return -1;
    }

    return 0;
}