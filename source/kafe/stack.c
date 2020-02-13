#include <kafe/stack.h>

#include <stdlib.h>
#include <string.h>

int stack_init(Stack *s)
{
    if (s == NULL)
        return -1;  // stack wasn't created properly
    
    s->content = (char**) malloc(STACK_SIZE * sizeof(char*));
    if (s->content == NULL)
    {
        free(s->content);
        return -2;  // couldn't init stack
    }

    for (int i=0; i < STACK_SIZE; ++i)
    {
        if ((s->content[i] = (char*) malloc(LINE_LENGTH)) == NULL)
        {
            free(s->content[i]);
            return -2;
        }
    }

    s->pos = 0;
    return 0;  // everything is fine
}

int stack_free(Stack *s)
{
    if (s == NULL)
        return -1;  // stack wasn't initialized properly or was already freed
    
    for (int i=0; i < STACK_SIZE; ++i)
    {
        free(s->content[i]);
    }

    free(s->content);
    return 0;
}

int stack_push(Stack *s, char c)
{
    int i = 0;
    // searching for somewhere to put the character
    for (; i < 128 && s->content[s->pos][i] != 0; ++i);

    if (i == 128)
        return -1;  // no more space to put character

    s->content[s->pos][i] = c;
    return 0;  // everything went fine
}

int stack_next(Stack *s)
{
    if (s->pos + 1 == STACK_SIZE)
        return -1;  // can not push to the stack
    
    s->pos++;
    return 0;  // everything went fine
}

int is_stack_empty(Stack *s)
{
    return (strlen(s->content[s->pos]) == 0) ? 1 : 0;
}

int stack_cmp_top(Stack *s, const char *value)
{
    return (strcmp(s->content[s->pos], value) == 0) ? 1 : 0;
}

int stack_pop(Stack *s)
{
    if (memset(s->content[s->pos], 0, LINE_LENGTH) == NULL)
        return -1;  // couldn't set memory to 0s
    return 0;
}