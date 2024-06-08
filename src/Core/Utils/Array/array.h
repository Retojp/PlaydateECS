#ifndef array_h
#define array_h

#include <stdlib.h>

typedef struct Array Array;

Array* ArrayCreate(int elementSize, void* (*realloc)(void*, size_t));
int ArrayGetSize(const Array *array);
void* ArrayGetElementAt(const Array *array, int index);
void AddElement(Array* array, const void* element);
void ArrayClean(Array *array);
void ArrayDestroy(Array *array);

#endif /* array_h */