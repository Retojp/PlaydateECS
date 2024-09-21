#include"ecsComponent.h"

Component* ComponentCreate(void* (*realloc)(void*,size_t), char* name, fnPtrVoid initialize, fnPtrVoidFloat update, fnPtrVoid destroy, void* data)
{
    Component* newComponent = realloc(0,sizeof(Component));
    newComponent->name=name;
    newComponent->realloc=realloc;
    newComponent->Initialize=initialize;
    newComponent->Update=update;
    newComponent->data=data;
    newComponent->Destroy=destroy;
    return newComponent;
}

void ComponentDestroy(Component* component)
{
    component->Destroy(component->data);
    component->name = realloc(component->name,0);
    component->data=NULL;
}