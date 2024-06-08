#include "array.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
    int size;
    int elementSize;
    int capacity;
    void* data;
    void* (*realloc)(void*, size_t);
} ArrayImpl;

Array* ArrayCreate(int elementSize, void* (*realloc)(void*, size_t))
{
    ArrayImpl *_array = realloc(0, sizeof(ArrayImpl));
    _array->elementSize = elementSize;
    _array->capacity = 0;
    _array->size = 0;
    _array->data = NULL;
    _array->realloc = realloc;
    return (Array*)_array;
}

int ArrayGetSize(const Array *array){
    const ArrayImpl *_array = (ArrayImpl*)array;
    return _array->size;
}

void* ArrayGetElementAt(const Array *array, int index){
    const ArrayImpl *_array = (ArrayImpl*)array;
    if(index<0 || index>=_array->size)
        return NULL;    
    return _array->data + index * _array->elementSize;
}

void AddElement(Array* array, const void* element)
{
    ArrayImpl *_array = (ArrayImpl*)array;
    int oldSize = _array->size;
    int newSize = oldSize + 1;
    if(newSize > _array->capacity){
        void* (*realloc)(void*,size_t) = _array->realloc;
        _array = realloc(_array,newSize*_array->elementSize);
        _array->capacity = newSize;
    }
    void* data = _array->data;
    memcpy(data + oldSize * _array->elementSize, element, _array->elementSize);
    _array->size = newSize;
}

void ArrayClean(Array *array){
    ArrayImpl *_array = (ArrayImpl*)array;
    void* (*realloc)(void*, size_t) = _array->realloc;
    if(_array->data){
        _array->data = realloc(_array->data,0);
        _array->size = 0;
        _array->capacity = 0;
    }
}
void ArrayDestroy(Array *array){
    ArrayClean(array);
    ArrayImpl *_array = (ArrayImpl*)array;
    _array->realloc(_array,0);
}
