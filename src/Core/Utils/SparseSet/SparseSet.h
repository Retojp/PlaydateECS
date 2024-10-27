#ifndef SparseSet_h
#define SparseSet_h

#include <stdlib.h>
#include <stdbool.h>

typedef struct SparseSet SparseSet;

SparseSet *SparseSetCreate(void* (*realloc)(void *, size_t), int maxSize, size_t elementSize);
void SparseSetAdd(SparseSet* sparseSet, int element, void* data);
bool SparseSetContains(SparseSet* sparseSet, int element);
void SparseSetRemove(SparseSet* sparseSet, int element);
void* SparseSetGetElement(SparseSet *sparseSet, int elementIndex);
void SparseSetIterate(SparseSet *sparseSet, void (*iterateFunc)(void*,int ,void*), void* userdata);

#endif