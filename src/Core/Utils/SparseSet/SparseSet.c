#include "SparseSet.h"
#include "../Array/array.h"
#include <string.h>

typedef struct SparseSetImpl 
{
    void* (*realloc)(void *, size_t);
    int* dense;
    int* sparse;
    Array* data;
    size_t elementSize;
    int n;
    int maxId;
} SparseSetImpl;

SparseSet *SparseSetCreate(void* (*realloc)(void *, size_t), int maxSize, int elementSize)
{
    SparseSetImpl *_sparseSet = realloc(0,sizeof(SparseSetImpl));
    _sparseSet->realloc = realloc;
    _sparseSet->n=0;
    int maxArraySize = maxSize*sizeof(int);
    _sparseSet->sparse = realloc(0,maxArraySize);
    _sparseSet->dense = realloc(0,maxArraySize);
    for (int i = 0; i < maxSize; i++)
    {
        _sparseSet->sparse[i] = -1;
        _sparseSet->dense[i] = -1;
    }
    
    _sparseSet->elementSize = elementSize;
    _sparseSet->data = ArrayCreate(elementSize,realloc);
    _sparseSet->maxId = maxSize;
    return (SparseSet*)_sparseSet;
}

void SparseSetAdd(SparseSet* sparseSet, int element, void* data)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    if(element >= _sparseSet->maxId || SparseSetContains(sparseSet,element))
        return;
    
    _sparseSet->dense[_sparseSet->n] = element;
    _sparseSet->sparse[element] = _sparseSet->n;
    
    int arraySize = ArrayGetSize(_sparseSet->data);

    if(arraySize>_sparseSet->n){
        void* elementToOverride = ArrayGetElementAt(_sparseSet->data,_sparseSet->n);
        memcpy(elementToOverride,data,_sparseSet->elementSize);
    }
    else{
        ArrayAddElement(_sparseSet->data,data);
    }

    ++_sparseSet->n;
}

bool SparseSetContains(SparseSet* sparseSet, int element)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    if(element >= _sparseSet->maxId)
        return false;

    int dense_index = _sparseSet->sparse[element];
    if(dense_index<0) {
        return false;
    }
    return dense_index < _sparseSet->n && _sparseSet->dense[dense_index] == element;
}

void SparseSetRemove(SparseSet *sparseSet, int element)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    if(element >= _sparseSet->maxId || !SparseSetContains(sparseSet,element))
        return;
    
    --_sparseSet->n;
    int dense_index = _sparseSet->sparse[element];
    int lastItem = _sparseSet->dense[_sparseSet->n];
    _sparseSet->dense[dense_index] = lastItem;
    _sparseSet->sparse[lastItem] = dense_index;
}

void* SparseSetGetElement(SparseSet *sparseSet, int elementIndex){
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    
    if(elementIndex >= _sparseSet->maxId || !SparseSetContains(sparseSet,elementIndex))
        return NULL;

    return ArrayGetElementAt(_sparseSet->data,_sparseSet->sparse[elementIndex]);
}

void SparseSetIterate(SparseSet *sparseSet, void (*iterateFunc)(void*, int ,void*), void* userdata)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    int i = 0;

    for(i=0;i<_sparseSet->n;i++)
    {
        iterateFunc(ArrayGetElementAt(_sparseSet->data,i), _sparseSet->dense[i], userdata);
    }
}

void SparseSetDestroy(SparseSet *sparseSet){
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    ArrayDestroy(_sparseSet->data);
    _sparseSet->realloc(_sparseSet->dense,0);
    _sparseSet->realloc(_sparseSet->sparse,0);
    _sparseSet->realloc(_sparseSet,0);
}