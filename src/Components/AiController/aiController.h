#ifndef ai_controller_h
#define ai_controller_h
#include "src/Core/Ecs/ecsComponent.h"
#include "src/Core/Utils/functionTypes.h"
#include "src/Components/Position/position.h"
#include "pd_api.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    Position* position;
    Position* ballPosition;
    float speed;
    PlaydateAPI* playdateAPI;
} AiController;

Component* AiControllerCreate(void* (*realloc)(void*,size_t),Position* position, Position* ballPosition, PlaydateAPI *pdAPI);

#endif