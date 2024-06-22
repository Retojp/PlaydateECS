#include"ecsComponent.h"

Component* ComponentCreate(void* (*realloc)(void*,size_t), fnPtr initialize, fnPtrFloat update)
{
    Component* newComponent = realloc(0,sizeof(Component));
    newComponent->Initialize=initialize;
    newComponent->Update=update;
    return newComponent;
}

void ComponentDestroy(Component* component)
{
    component->realloc(component,0);
}