#ifndef SparseSet_h
#define SparseSet_h

#include <stdlib.h>
#include <stdbool.h>

typedef struct SparseSet SparseSet;

SparseSet* SparseSetCreate(void* (*realloc)(void*,size_t), int maxId);
void SparseSetAdd(SparseSet* sparseSet, int element);
bool SparseSetContains(SparseSet* sparseSet, int element);
void SparseSetRemove(SparseSet* sparseSet, int element);
void SparseSetIterate(SparseSet* sparseSet, void (*iterateFunc)(int));

#endif