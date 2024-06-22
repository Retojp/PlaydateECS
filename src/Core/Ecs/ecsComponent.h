#ifndef ecsComponent_h
#define ecsComponent_h

#include <stdlib.h>

typedef int (*fnPtr)(void);
typedef int (*fnPtrFloat)(float);

typedef struct{
    fnPtr Initialize;
    fnPtrFloat Update;
    void* (*realloc)(void*,size_t);
} Component;

Component* ComponentCreate(void* (*realloc)(void*,size_t), fnPtr initialize, fnPtrFloat update);
void ComponentDestroy(Component* component);

#endif