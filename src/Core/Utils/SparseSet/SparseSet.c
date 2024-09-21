#include "SparseSet.h"

typedef struct SparseSetImpl 
{
    void* (*realloc)(void *, size_t);
    int* dense;
    int* sparse;
    int n;
    int maxId;
} SparseSetImpl;

SparseSet *SparseSetCreate(void* (*realloc)(void *, size_t), int maxSize)
{
    SparseSetImpl *_sparseSet = realloc(0,sizeof(SparseSetImpl));
    _sparseSet->realloc = realloc;
    _sparseSet->n=0;
    size_t maxArraySize = maxSize*sizeof(int);
    _sparseSet->sparse = realloc(0,maxArraySize);
    _sparseSet->dense = realloc(0,maxArraySize);
    _sparseSet->maxId = maxSize;
    return (SparseSet*)_sparseSet;
}

void SparseSetAdd(SparseSet* sparseSet, int element)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    if(element >= _sparseSet->maxId || SparseSetContains(sparseSet,element))
        return;
    
    _sparseSet->dense[_sparseSet->n] = element;
    _sparseSet->sparse[element] = _sparseSet->n;
    
    ++_sparseSet->n;
}

bool SparseSetContains(SparseSet* sparseSet, int element)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    if(element >= _sparseSet->maxId)
        return;

    int dense_index = _sparseSet->sparse[element];
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

void SparseSetIterate(SparseSet *sparseSet, void (*iterateFunc)(int))
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    int i = 0;
    for(i=0;i<_sparseSet->n;i++)
    {
        iterateFunc(_sparseSet->dense[i]);
    }
}
