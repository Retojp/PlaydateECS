#ifndef position_h
#define position_h
#include "src/Core/Ecs/ecsComponent.h"
#include "src/Core/Utils/functionTypes.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    int x;
    int y;
} Position;

Component* PositionCreate(void *(*realloc)(void *, size_t),int x,int y);
void PositionDestroy(Position* position);

#endif