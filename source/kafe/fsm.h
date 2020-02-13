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
    char *closing_tag = (char*) calloc(LINE_LENGTH, sizeof(char));

    // reading characters from file until end
    for (c = fgetc(pFile); !feof(pFile); c = fgetc(pFile))
    {
        switch (s.state)
        {
            case s.Start:
                if (c == '<')
                    s.state = s.TagStart;
                else if (c != ' ')  // we allow only skipping spaces
                {
                    printf("Can't skip a character other than a space\n");
                    return -1;
                }
                break;
            
            case s.TagStart:
                // a tag can only be composed of azAZ09
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                {
                    if (stack_push(&stack, c) != 0)
                    {
                        printf("Couldn't push to stack\n");
                        return -1;
                    }
                    s.state = s.TagNameFeed;
                }
                else if (c == '/')
                {
                    s.state = s.ClosingTagStart;
                }
                else if (c == ' ')  // skip trailing spaces
                {
                    continue;
                }
                else
                {
                    printf("Invalid tag start\n");
                    return -2;
                }
                break;
            
            case s.TagNameFeed:
                // a tag can only be composed of azAZ09
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                {
                    if (stack_push(&stack, c) != 0)
                    {
                        printf("Couldn't push to stack\n");
                        return -1;
                    }
                }
                else if (c == ' ')  // if space, then maybe we have attributes
                {
                    if (stack_next(&stack) != 0)
                    {
                        printf("Couldn't add another element to the stack\n");
                        return -1;
                    }
                    s.state = s.TagAttr;
                }
                break;
            
            case s.TagNameEnd:
                break;
            
            case s.TagAttr:
                // a tag attribute can only be composed of azAZ09="'
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '"' || c == '=')
                    continue;
                else if (c == ' ')  // skip spaces
                    continue;
                else if (c == '>')
                    s.state = s.TagEnd;
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