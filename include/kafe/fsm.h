#ifndef fsm_h
#define fsm_h

#include <stdio.h>

typedef struct
{
    int Start = 0,
        End = 1;
} State;
const State STATE;

int fsm_run(FILE *pFile);

#endif  // fsm_h