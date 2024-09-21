#ifndef draw_h
#define draw_h
#include "src/Core/Ecs/ecsComponent.h"
#include "src/Core/Utils/functionTypes.h"
#include "src/Components/Position/position.h"
#include "pd_api.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    Position* position;
    int width;
    int height;
    PlaydateAPI* playdateAPI;
} Draw;

Component* DrawCreate(void* (*realloc)(void*,size_t),Position* position,int width,int height, PlaydateAPI *pdAPI);
void DrawDestroy(Draw* position);

#endif