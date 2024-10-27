#ifndef ecs_h
#define ecs_h

#include "src/Core/Utils/SparseSet/SparseSet.h"

#define MAX_COMPONENTS 64
#define MAX_ENTITIES 1000

typedef void* componentPtr;
typedef void* userdataPtr;

typedef struct Ecs Ecs;

Ecs* EcsCreate(void* (*realloc)(void*,size_t));
int EcsRegisterComponent(Ecs *ecs, size_t componentSize);
void EcsAddComponentTo(Ecs *ecs, int componentType, int entityId, componentPtr component);
void EcsRemoveComponentFrom(Ecs* ecs, int componentType, int entityId);
void EcsIterateOver(Ecs *ecs, int componentType, void (*iterateFunc)(componentPtr, int, userdataPtr),userdataPtr userdata);
void *EcsGetComponent(Ecs *ecs, int componentType, int entityId);
void EcsDestroy(Ecs* ecs);

#endif