#include "SparseSet.h"

typedef struct SparseSetImpl 
{
    void* (*realloc)(void *, size_t);
    Array* dense;
    int* sparse;
    int n;
    int maxId;
    fnSparseSetGetElementIndex GetElementIndex;
    fnSparseSetSetElementAt SetElementAt;
} SparseSetImpl;

SparseSet *SparseSetCreate(
    void* (*realloc)(void *, size_t),
    size_t elementSize,
    int maxSize,
    fnSparseSetGetElementIndex GetElementIndex,
    fnSparseSetSetElementAt SetElementAt
  )
{
    SparseSetImpl *_sparseSet = realloc(0,sizeof(SparseSetImpl));
    _sparseSet->realloc = realloc;
    _sparseSet->n=0;
    size_t maxArraySize = maxSize*sizeof(int);
    _sparseSet->sparse = realloc(0,maxArraySize);
    _sparseSet->dense = ArrayCreate(elementSize, realloc);
    _sparseSet->maxId = maxSize;
    _sparseSet->GetElementIndex = GetElementIndex;
    _sparseSet->SetElementAt = SetElementAt;
    return (SparseSet*)_sparseSet;
}

void SparseSetAdd(SparseSet* sparseSet, void* element)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    int elementIndex = _sparseSet->GetElementIndex(element);
    if(elementIndex >= _sparseSet->maxId || SparseSetContains(sparseSet,elementIndex))
        return;
    
    if(_sparseSet->n >= ArrayGetSize(_sparseSet->dense))
    {
        ArrayAddElement(_sparseSet->dense,element);
    }
    else
    {
        _sparseSet->SetElementAt(_sparseSet->dense, _sparseSet->n, element);
    }
    _sparseSet->sparse[elementIndex] = _sparseSet->n;
    
    ++_sparseSet->n;
}

bool SparseSetContains(SparseSet* sparseSet, int elementIndex)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    if(elementIndex >= _sparseSet->maxId)
        return false;

    int dense_index = _sparseSet->sparse[elementIndex];
    if(dense_index >= ArrayGetSize(_sparseSet->dense))
        return false;
    return _sparseSet->GetElementIndex(ArrayGetElementAt(_sparseSet->dense, dense_index)) == elementIndex;
}

void SparseSetRemove(SparseSet *sparseSet, int elementIndex)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    if(elementIndex >= _sparseSet->maxId || !SparseSetContains(sparseSet,elementIndex))
        return;
    
    --_sparseSet->n;
    int dense_index = _sparseSet->sparse[elementIndex];
    void* lastItem =  ArrayGetElementAt(_sparseSet->dense,_sparseSet->n);
    _sparseSet->SetElementAt(_sparseSet->dense,dense_index,lastItem);
    
    _sparseSet->sparse[_sparseSet->GetElementIndex(lastItem)] = dense_index;
}

void SparseSetIterate(SparseSet *sparseSet, void (*iterateFunc)(void*,void*), void* userdata)
{
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    int i = 0;
    for(i=0;i<_sparseSet->n;i++)
    {
        iterateFunc(ArrayGetElementAt(_sparseSet->dense,i),userdata);
    }
}

void SparseSetDestroy(SparseSet *sparseSet){
    SparseSetImpl* _sparseSet = (SparseSetImpl*)sparseSet;
    ArrayDestroy(_sparseSet->dense);
    _sparseSet->realloc(_sparseSet,0);
}