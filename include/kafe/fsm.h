#ifndef fsm_h
#define fsm_h

#include <stdio.h>

typedef struct
{
    const int Start = 0,
        TagStart    = 1,
        TagNameFeed = 2,
        TagNameEnd  = 3,
        TagAttr     = 4,
        TagEnd      = 5,
        ClosingTagStart = 6
        ;

    int state = Start;
} State;

int fsm_run(FILE *pFile);

#endif  // fsm_h