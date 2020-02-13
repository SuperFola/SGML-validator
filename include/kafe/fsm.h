#ifndef fsm_h
#define fsm_h

#include <stdio.h>

enum State
{
    STATE_Start,
    STATE_TagStart,
    STATE_TagNameFeed,
    STATE_TagAttr,
    STATE_TagEnd,
    STATE_ClosingTagStart
};

int fsm_run(FILE *pFile);

#endif  // fsm_h