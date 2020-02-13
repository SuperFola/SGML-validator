#ifndef stack_h
#define stack_h

#define STACK_SIZE 2048
#define LINE_LENGTH 64

typedef struct
{
    char **content;
    unsigned pos;
} Stack;

int stack_init(Stack *s);
int stack_free(Stack *s);

int stack_push(Stack *s, char c);
int stack_next(Stack *s);
int is_stack_empty(Stack *s);
int stack_cmp_top(Stack *s, const char *value);
int stack_pop(Stack *s);

#endif  // stack_h