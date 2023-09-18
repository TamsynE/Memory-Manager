#ifndef project2_h
#define project2_h

#include <stdbool.h>

void CreateMemoryManager(int sizeTotal, bool bf);
void* mallocMem(int size, bool bf);
NODE* CheckBusyList(void* data);
NODE* CheckFreeListBefore(NODE* curr);
NODE* CheckFreeListAfter(NODE* curr);
void* freeMem(void* data);
void DumpFree();
void DumpBusy();
void DestroyMem();

#endif