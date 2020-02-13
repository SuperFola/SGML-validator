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
    int i = 0;

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
                    goto end;
                }
                break;
            
            case s.TagStart:
                // a tag can only be composed of azAZ09
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                {
                    if (stack_push(&stack, c) != 0)
                    {
                        printf("Couldn't push to stack\n");
                        goto end;
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
                    goto end;
                }
                break;
            
            case s.TagNameFeed:
                // a tag can only be composed of azAZ09
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                {
                    if (stack_push(&stack, c) != 0)
                    {
                        printf("Couldn't push to stack\n");
                        goto end;
                    }
                }
                else if (c == ' ' || c == '>')  // if space, then maybe we have attributes
                {
                    if (stack_next(&stack) != 0)
                    {
                        printf("Couldn't add another element to the stack\n");
                        goto end;
                    }
                    s.state = s.TagAttr;
                }
                else
                {
                    printf("Wrong character when feeding tag name: %c\n", c);
                    goto end;
                }
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
                // skip everything until a '<'
                if (c == '<')
                    s.state = s.TagStart;
                break;
            
            case s.ClosingTagStart:
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
                else if (c == '>')
                {
                    if (stack_cmp_top(&stack, closing_tag) == 0)
                    {
                        // do not pop from empty stack
                        if (stack.pos == 0)
                        {
                            printf("Can not pop from empty stack\n");
                            goto end;
                        }

                        if (stack_pop(&stack) != 0)
                        {
                            printf("Can not pop from stack\n");
                            goto end;
                        }
                    }
                }
                else
                {
                    printf("Wrong character in closing tag name");
                    goto end;
                }
                break;

            default:
                break;
        }

        if (stack->pos != 0)
        {
            printf("At least a tag wasn't closed properly!\n");
            goto end;
        }
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