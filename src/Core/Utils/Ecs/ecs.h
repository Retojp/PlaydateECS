#ifndef ecs_h
#define ecs_h

#include "src/Core/Utils/SparseSet/SparseSet.h"

#define MAX_COMPONENTS 64
#define MAX_ENTITIES 100

typedef void* componentPtr;
typedef void* userdataPtr;

typedef struct Ecs Ecs;

Ecs* EcsCreate(void* (*realloc)(void*,size_t));
int EcsRegisterComponent(Ecs *ecs, size_t componentSize,fnSparseSetGetElementIndex GetIndex,fnSparseSetSetElementAt SetElement);
void EcsAddComponentTo(Ecs* ecs, int componentType, componentPtr component);
void EcsRemoveComponentFrom(Ecs* ecs, int componentType, int entityId);
void EcsIterateOver(Ecs *ecs, int componentType, void (*iterateFunc)(componentPtr, userdataPtr),userdataPtr userdata);
void* EcsGetComponent(Ecs* ecs, int entityId, int componentType);
void EcsDestroy(Ecs* ecs);

#endif