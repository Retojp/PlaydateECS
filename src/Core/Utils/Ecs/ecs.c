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

void EcsAddComponentTo(Ecs *ecs, int componentType, componentPtr component)
{
    EcsImpl* _ecs = (EcsImpl*)ecs;
    if(_ecs->registered_count<=componentType)
        return;
    SparseSetAdd(_ecs->components[componentType],component);
    return;
}

void EcsRemoveComponentFrom(Ecs *ecs, int componentType, int entityId)
{
    EcsImpl* _ecs = (EcsImpl*)ecs;
    if(_ecs->registered_count<=componentType)
        return;
    SparseSetRemove(_ecs->components[componentType],entityId);
}

void EcsIterateOver(Ecs *ecs, int componentType, void (*iterateFunc)(componentPtr, userdataPtr),userdataPtr userdata)
{
    EcsImpl* _ecs = (EcsImpl*)ecs;
    if(_ecs->registered_count<=componentType)
        return;
    SparseSetIterate(_ecs->components[componentType],iterateFunc,userdata);
}

void EcsDestroy(Ecs *ecs)
{
    EcsImpl* _ecs = (EcsImpl*)ecs;
    int i = 0;
    for(i=0;i<_ecs->registered_count;i++){
        SparseSetRemove(_ecs->components[i],i);
    }
    _ecs->realloc(ecs,0);
}
