#include"src/Core/Ecs/ecsComponent.h"
#include"ecsEntity.h"
#include"src/Core/Utils/Array/array.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    Array* components;
} EntityImpl;

Entity* EntityCreate(void* (*realloc)(void*, size_t))
{
    EntityImpl* newEntity = realloc(0,sizeof(EntityImpl));
    newEntity->realloc = realloc;
    newEntity->components = ArrayCreate(sizeof(Component),realloc);
    return (Entity*)newEntity;
}

void EntityAddComponent(Entity* entity, Component* component){
    EntityImpl *_entity = (EntityImpl*)entity;
    ArrayAddElement(_entity->components,component);
}

void EntityInitialize(Entity* entity)
{
    EntityImpl *_entity = (EntityImpl*)entity;
    int componentsCount = ArrayGetSize(_entity->components);
    int i;
    for(i=0; i<componentsCount; i++){
        Component *component = (Component*)ArrayGetElementAt(_entity->components,i);
        component->Initialize();
    }
}

void EntityUpdate(Entity* entity, float deltatime){
    EntityImpl *_entity = (EntityImpl*)entity;
    int componentsCount = ArrayGetSize(_entity->components);
    int i;
    for(i=0; i<componentsCount; i++){
        Component *component = (Component*)ArrayGetElementAt(_entity->components,i);
        component->Update(deltatime);
    }
}

void EntityDestroy(Entity* entity){
    EntityImpl *_entity = (EntityImpl*)entity;
    int componentsCount = ArrayGetSize(_entity->components);
    int i;
    for(i=0; i<componentsCount; i++)
    {
        Component *component = (Component*)ArrayGetElementAt(_entity->components,i);
        ComponentDestroy(component);
    }
    ArrayDestroy(_entity->components);
    _entity->realloc(_entity,0);
}
