#ifndef SparseSet_h
#define SparseSet_h

#include <stdlib.h>
#include <stdbool.h>
#include "src/Core/Utils/Array/array.h"

typedef struct SparseSet SparseSet;
typedef int (*fnSparseSetGetElementIndex)(void*);
typedef void (*fnSparseSetSetElementAt)(Array*, int, void*);

SparseSet *SparseSetCreate(
    void* (*realloc)(void *, size_t),
    size_t elementSize,
    int maxSize,
    fnSparseSetGetElementIndex GetElementIndex,
    fnSparseSetSetElementAt SetElementAt
  );
void SparseSetAdd(SparseSet* sparseSet, void* element);
bool SparseSetContains(SparseSet* sparseSet, int elementIndex);
void SparseSetRemove(SparseSet *sparseSet, int elementIndex);
void SparseSetIterate(SparseSet *sparseSet, void (*iterateFunc)(void*,void*), void* userdata);

#endif