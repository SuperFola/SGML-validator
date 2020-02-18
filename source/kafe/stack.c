#include <kafe/stack.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack_init(Stack *s)
{
    if (s == NULL)
        return -1;  // stack wasn't created properly
    
    if ((s->first = (Element*) malloc(sizeof(Element))) == NULL)
    {
        free(s->first);
        return -2;  // couldn't init stack
    }
    memset(s->first, 0, sizeof(Element));

    if ((s->first->content = (char*) malloc(sizeof(char) * LINE_LENGTH)) == NULL)
    {
        free(s->first->content);
        return -2;
    }
    memset(s->first->content, 0, sizeof(char) * LINE_LENGTH);

    return 0;  // everything is fine
}

void element_free(Element *e)
{
    if (e->next != NULL)
    {
        element_free(e->next);
    }
    free(e->content);
    free(e);
}

int stack_free(Stack *s)
{
    if (s == NULL)
        return -1;  // stack wasn't initialized properly or was already freed

    if (s->first != NULL)
        element_free(s->first);
    return 0;
}

int stack_push(Stack *s, char c)
{
    int i = 0;
    // searching for somewhere to put the character
    for (; i < 128 && s->first->content[i] != 0; ++i);

    if (i == 128)
        return -1;  // no more space to put character

    s->first->content[i] = c;
    return 0;  // everything went fine
}

int stack_next(Stack *s)
{
    Element *old = s->first;
    if ((s->first = (Element*) malloc(sizeof(Element))) == NULL)
    {
        stack_free(s);
        printf("Couldn't allocate new element on stack, quitting\n");
        return -1;
    }
    memset(s->first, 0, sizeof(Element));

    if ((s->first->content = (char*) malloc(sizeof(char) * LINE_LENGTH)) == NULL)
    {
        stack_free(s);
        printf("Couldn't allocate new element on stack, quitting\n");
        return -1;
    }
    memset(s->first->content, 0, sizeof(char) * LINE_LENGTH);
    s->first->next = old;

    return 0;  // everything went fine
}

int is_stack_empty(Stack *s)
{
    if (s->first == NULL)
        return -1;
    return (strlen(s->first->content) == 0) ? 1 : 0;
}

int stack_cmp_top(Stack *s, const char *value)
{
    return strcmp(s->first->content, value);
}

int stack_pop(Stack *s)
{
    Element *old = s->first->next;
    free(s->first->content);
    free(s->first);
    s->first = old;
    return 0;
}

int stack_depth(Stack *s)
{
    int depth = 0;
    Element *e = s->first;
    if (e == NULL)
        return depth;
    
    depth++;
    while (1)
    {
        e = e->next;
        if (e == NULL)
            break;
        depth++;
    }

    return depth;
}

void stack_print(Stack *s)
{
    printf("Depth: %d\n", stack_depth(s));
    Element *e = s->first;
    if (s->first == NULL)
    {
        printf("== empty ==\n");
        return;
    }
    int i = 0;
    while (1)
    {
        printf("[%d] %s\n", i, e->content);
        e = e->next;
        i++;
        if (e == NULL)
            break;
    }
}