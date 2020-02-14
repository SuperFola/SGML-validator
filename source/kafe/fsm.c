#include <kafe/fsm.h>
#include <kafe/stack.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fsm_run(FILE *pFile)
{
    Stack stack;
    if (stack_init(&stack) != 0)
    {
        printf("Couldn't initialize the stack!\n");
        return -1;
    }

    int s = STATE_Start;
    char *closing_tag = (char*) calloc(LINE_LENGTH, sizeof(char));  // needed to store the name of the closing tag we found
    int i = 0;  // index of current character added to the closing tag

    // reading characters from file until end
    for (char c = fgetc(pFile); !feof(pFile); c = fgetc(pFile))
    {
    #ifdef FSM_DEBUG
        stack_print(&stack);
        printf("state: %d\n================\n", s);
    #endif  // FSM_DEBUG

        switch (s)
        {
            case STATE_Start:            // 0
                if (c == '<')  // closing tag, change state
                    s = STATE_TagStart;
                else if (c != ' ' && c != '\r' && c != '\n')  // we allow only skipping spaces
                {
                    printf("Can't skip a character other than a space: 0x%d\n", (int) c);
                    goto end;
                }
                break;
            
            case STATE_TagStart:         // 1
                // a tag can only be composed of azAZ09
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                {
                    // first element isn't empty, let's create a new one
                    if (is_stack_empty(&stack) != 1)
                    {
                        if (stack_next(&stack) != 0)
                        {
                            printf("Couldn't add another element to the stack\n");
                            goto end;
                        }
                    }

                    if (stack_push(&stack, c) != 0)
                    {
                        printf("Couldn't push to stack\n");
                        goto end;
                    }
                    s = STATE_TagNameFeed;
                }
                else if (c == '/')  // we found a closing tag
                {
                    s = STATE_ClosingTagStart;
                }
                else if (c == ' ' || c == '\r' || c == '\n')  // skip trailing spaces
                {
                    continue;
                }
                else
                {
                    printf("Invalid tag start\n");
                    goto end;
                }
                break;
            
            case STATE_TagNameFeed:      // 2
                // a tag can only be composed of azAZ09
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                {
                    if (stack_push(&stack, c) != 0)
                    {
                        printf("Couldn't push to stack\n");
                        goto end;
                    }
                }
                else if (c == ' ')  // if space, then maybe we have attributes
                {
                    s = STATE_TagAttr;
                }
                else if (c == '>')
                {
                    s = STATE_TagEnd;
                }
                else
                {
                    printf("Wrong character when feeding tag name: %c\n", c);
                    goto end;
                }
                break;
            
            case STATE_TagAttr:          // 3
                // a tag attribute can only be composed of azAZ09="'
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '"' || c == '=')
                    continue;
                else if (c == ' ')  // skip spaces
                    continue;
                else if (c == '>')
                {
                    s = STATE_TagEnd;
                }
                break;
            
            case STATE_TagEnd:           // 4
                // skip everything until a '<'
                if (c == '<')
                    s = STATE_TagStart;
                break;
            
            case STATE_ClosingTagStart:  // 5
                // a tag can only be composed of azAZ09
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                {
                    closing_tag[i] = c;
                    ++i;
                    if (i >= LINE_LENGTH)
                    {
                        printf("Tag name too long %s\n", closing_tag);
                        goto end;
                    }
                }
                else if (c == '>')  // end of tag, check if it's valid
                {
                    if (stack_cmp_top(&stack, closing_tag) == 0)
                    {
                        i = 0;
                        memset(closing_tag, 0, LINE_LENGTH * sizeof(char));

                        if (stack_pop(&stack) != 0)
                        {
                            printf("Can not pop from stack\n");
                            goto end;
                        }
                    }
                    else
                    {
                        printf("ERROR: found closing tag '%s' but got opening tag '%s'\n", closing_tag, stack.first->content);
                        goto end;
                    }
                    s = STATE_Start;
                }
                else
                {
                    printf("Wrong character in closing tag name: 0x%d\n", (int) c);
                    goto end;
                }
                break;

            default:
                break;
        }
    }

    // checking if we have tags left on the stack
    if (stack_depth(&stack) > 0)
    {
        printf("At least a tag wasn't closed properly!\n");
        stack_print(&stack);
        goto end;
    }
    else
    {
        printf("SGML is valid\n");
    }

end:
    free(closing_tag);
    if (stack_free(&stack) != 0)
    {
        printf("Couldn't free the stack!\n");
        return -1;
    }

    return 0;
}