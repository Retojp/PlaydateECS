#ifndef ecsEntity_h
#define ecsEntity_h

#include <stdlib.h>

typedef struct Entity Entity;

Entity* EntityCreate(void* (*realloc)(void*, size_t));
void EntityAddComponent(Entity* entity, Component* component);
void EntityInitialize(Entity* entity);
void EntityUpdate(Entity* entity, float deltatime);
void EntityDestroy(Entity* entity);

#endif