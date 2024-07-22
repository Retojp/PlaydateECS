#ifndef transform_h
#define transform_h
#include "src/Core/Ecs/ecsComponent.h"
#include "src/Core/Utils/functionTypes.h"
#include "src/Components/Position/position.h"
#include "pd_api.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    Position* position;
} Transform;

Component* TransformCreate(void* (*realloc)(void*,size_t),Position* position);
void Translate(Transform* transform, int deltaX, int deltaY);
void TransformDestroy(Transform* position);

#endif