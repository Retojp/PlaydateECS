#include "ecs.h"

typedef struct EcsImpl{
    SparseSet* components[MAX_COMPONENTS];
    unsigned int registered_count;
    void* (*realloc)(void*,size_t);
} EcsImpl;

Ecs *EcsCreate(void *(*realloc)(void *, size_t))
{
    EcsImpl* _ecs = realloc(0,sizeof(EcsImpl));
    _ecs->realloc = realloc;
    _ecs->registered_count=0;
    return (Ecs*)_ecs;
}

void *EcsGetComponent(Ecs *ecs, int entityId, int componentType)
{
    EcsImpl* _ecs = (EcsImpl*)ecs;

    return SparseSetGetElement(_ecs->components[componentType],entityId);
}

int EcsRegisterComponent(Ecs *ecs, size_t componentSize,fnSparseSetGetElementIndex GetIndex,fnSparseSetSetElementAt SetElement)
{
    EcsImpl* _ecs = (EcsImpl*)ecs;
    if(_ecs->registered_count>=MAX_COMPONENTS)
        return -1;

    _ecs->components[_ecs->registered_count] = SparseSetCreate(_ecs->realloc,componentSize,MAX_ENTITIES,GetIndex,SetElement);
    return _ecs->registered_count++;
}

int EcsAddComponentTo(Ecs *ecs, int componentType, void *component)
{
    EcsImpl* _ecs = (EcsImpl*)ecs;
    SparseSetAdd(_ecs->components[componentType],component);
    return 0;
}
