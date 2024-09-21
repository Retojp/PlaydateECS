#ifndef box_collider
#define box_collider
#define BOX_COLLIDER_COMPONENT_NAME "BoxCollider"

#include "src/Core/Utils/Array/array.h"
#include "src/Core/Ecs/ecsComponent.h"
#include "src/Components/Position/position.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    int width;
    int height;
    Position* position;
} BoxCollider;

Component* BoxColliderCreate(void* (*realloc)(void*,size_t), int width, int height, Position* Position);
// Here are signs that proper ECS would be better
int BoxColliderCollisionCheck(BoxCollider* box1, BoxCollider* box2);

#endif