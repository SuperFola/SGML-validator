#ifndef stack_h
#define stack_h

#define LINE_LENGTH 64

typedef struct Element Element;
struct Element
{
    char *content;
    Element *next;
};

typedef struct
{
    Element *first;
} Stack;

// the stack object must have been created beforehand
int stack_init(Stack *s);
// liberate memory used by the stack
int stack_free(Stack *s);

// push a single char to the first element of the stack
int stack_push(Stack *s, char c);
// create a new element on top of the stack
int stack_next(Stack *s);
// check if the top element of the stack is empty
int is_stack_empty(Stack *s);
// compare the value of the top most element of the stack with a given value (using strcmp behind)
int stack_cmp_top(Stack *s, const char *value);
// pop the top element from the stack
int stack_pop(Stack *s);
// get the depth of the stack
int stack_depth(Stack *s);
// print the values on the stack, from the top most to the bottom one
void stack_print(Stack *s);

#endif  // stack_h