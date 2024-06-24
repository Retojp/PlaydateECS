#ifndef draw_h
#define draw_h
#include "src/Core/Ecs/ecsComponent.h"
#include "src/Core/Utils/functionTypes.h"
#include "src/Components/Position/position.h"
#include "pd_api.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    Position* position;
    PlaydateAPI* playdateAPI;
} Draw;

Component* DrawCreate(void* (*realloc)(void*,size_t),Position* position, PlaydateAPI *pdAPI);
void DrawDestroy(Draw* position);

#endif