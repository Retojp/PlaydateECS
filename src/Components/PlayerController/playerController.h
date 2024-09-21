#ifndef player_controller_h
#define player_controller_h
#include "src/Core/Ecs/ecsComponent.h"
#include "src/Core/Utils/functionTypes.h"
#include "src/Components/Position/position.h"
#include "pd_api.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    Position* position;
    PlaydateAPI* playdateAPI;
} PlayerController;

Component* PlayerControllerCreate(void* (*realloc)(void*,size_t),Position* position, PlaydateAPI *pdAPI);

#endif