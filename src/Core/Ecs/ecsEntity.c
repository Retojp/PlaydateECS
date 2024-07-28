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
        component->Initialize(component->data);
    }
}

void EntityUpdate(Entity* entity, float deltatime){
    EntityImpl *_entity = (EntityImpl*)entity;
    int componentsCount = ArrayGetSize(_entity->components);
    int i;
    for(i=0; i<componentsCount; i++){
        Component *component = (Component*)ArrayGetElementAt(_entity->components,i);
        component->Update(component->data,deltatime);
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
        component = NULL;
    }
    ArrayDestroy(_entity->components);
}

int EntityGetSize(void){
    return sizeof(EntityImpl);
}

Component* EntityGetComponent(Entity *entity, char *name)
{
    EntityImpl *_entity = (EntityImpl*)entity;
    int componentsCount = ArrayGetSize(_entity->components);
    int i;
    for(i=0; i<componentsCount; i++){
        Component *component = (Component*)ArrayGetElementAt(_entity->components,i);
        if(strcmp(component->name,name) == 0)
            return component;
    }
    return NULL;
}
