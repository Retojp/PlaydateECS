#ifndef ecsComponent_h
#define ecsComponent_h

#include <stdlib.h>
#include "src/Core/Utils/functionTypes.h"
#include <string.h>

typedef struct{
    char* name;
    fnPtrVoid Initialize;
    fnPtrVoid Destroy;
    fnPtrVoidFloat Update;
    void* (*realloc)(void*,size_t);
    void* data;
} Component;

Component* ComponentCreate(void* (*realloc)(void*,size_t), char* name, fnPtrVoid initialize, fnPtrVoidFloat update, fnPtrVoid destroy, void* data);
void ComponentDestroy(Component* component);

#endif