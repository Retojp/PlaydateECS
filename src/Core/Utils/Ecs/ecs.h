#ifndef ecs_h
#define ecs_h

#include "src/Core/Utils/SparseSet/SparseSet.h"

#define MAX_COMPONENTS 64
#define MAX_ENTITIES 100

typedef struct Ecs Ecs;

Ecs* EcsCreate(void* (*realloc)(void*,size_t));
int EcsRegisterComponent(Ecs *ecs, size_t componentSize,fnSparseSetGetElementIndex GetIndex,fnSparseSetSetElementAt SetElement);
int EcsAddComponentTo(Ecs* ecs, int componentType, void* component);
void* EcsGetComponent(Ecs* ecs, int entityId, int componentType);

#endif