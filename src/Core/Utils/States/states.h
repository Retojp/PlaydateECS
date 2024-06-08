#ifndef states_h
#define states_h

#include<stdlib.h>

typedef int (*fnPtr)(void);
typedef int (*fnPtrFloat)(float);

typedef struct
{
    fnPtr enter;
    fnPtrFloat update;
    fnPtrFloat draw;
    fnPtr exit;
} State;

typedef struct
{
    State *current;
} StateManager;

int StateManagerUpdate(StateManager *StateManager, float deltaTime);
int StateManagerDraw(StateManager *StateManager, float deltaTime);
int StateManagerChangeTo(StateManager *StateManager, State *newState);

#endif /*states_h*/