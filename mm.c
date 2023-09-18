/*
Memory Manager
Allocates memory either by first-fit or best-fit, and frees memory (with coalescing if necessary)
file: mm.c
author: Tamsyn Evezard, Andie Perreira, Fatima Nava
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "project1.h"
#include "project2.h"

// Create Memory Manager
LLIST* freeList;
LLIST* busyList;

void CreateMemoryManager(int sizeTotal, bool bf)
{
    freeList = CreateList();
    busyList = CreateList();
    Insert(freeList, NULL, 0, sizeTotal, bf);
}


// Allocate Memory - First Fit & Best Fit

void* mallocMem(int size, bool bf)
{
    int idx = busyList -> count;

    if(size <= 0)
    {
        return NULL;
    }
    // SORT freeList for best fit allocation
    
    if(bf == true) 
    {
        SortList(freeList);
    }
    
    NODE* walker = freeList -> head;

        while(walker != NULL)
        {
            if(size == walker -> size)
            {
                void* allocAddress = walker -> data;
                RemoveNode(freeList, walker -> data);
                Insert(busyList, walker -> data, idx, size, false);
                return allocAddress;
            }

            else if(size < walker -> size)
            {
                void* allocAddress = walker -> data;
                Insert(busyList, walker -> data, idx, size, false);
                walker -> data = walker -> data + size;
                walker -> size = walker -> size - size;
                return allocAddress;
            }

            walker = walker -> next;
        }
    return NULL;
}

NODE* CheckBusyList(void* data) // find node to free from busy
{
    NODE* walker = busyList -> head;

    while(walker != NULL && data != walker -> data)
    { 
        walker = walker -> next;
    }
    return walker;
}

NODE* CheckFreeListBefore(NODE* curr) // check if node before deallocation node is in freeList
{
    NODE* freeWalker = freeList -> head;

    while(freeWalker != NULL && freeWalker-> data + freeWalker -> size != curr -> data)
    {
        freeWalker = freeWalker -> next;
    }
    return freeWalker;
}
NODE* CheckFreeListAfter(NODE* curr) // check if node after deallocation node is in freeList
{
    NODE* freeWalker = freeList -> head;

    while(freeWalker != NULL && curr -> data + curr -> size != freeWalker -> data)
    {
        freeWalker = freeWalker -> next;
    }
    return freeWalker;
}

// Free Memory (w/ coalescing)
void* freeMem(void* data) 
{
    NODE* curr = CheckBusyList(data);
    if(curr == NULL)
    {
        printf("That address cannot be freed.\n");
    }
    NODE* beforeNode = CheckFreeListBefore(curr);  // if not in freeList - will return NULL
    NODE* afterNode = CheckFreeListAfter(curr); // if not in freeList - will return NULL

    void* allocAddress = curr -> data;
    int allocSize = curr -> size;
    
    RemoveNode(busyList, allocAddress);
    
    // coalesce with block before and after
    if(beforeNode != NULL && afterNode != NULL)
    {
        beforeNode -> size = (beforeNode -> size) + (allocSize) + (afterNode -> size); // merge nodes
        allocAddress = beforeNode -> data;
        allocSize = beforeNode -> size;
        RemoveNode(freeList, afterNode -> data);
        return allocAddress; 
    }

    // coalesce with block after
    else if(beforeNode == NULL && afterNode != NULL)
    {
        afterNode -> size += allocSize;
        afterNode -> data -= allocSize;
        free(beforeNode);
        return allocAddress; 
    }

    // no coalescing
    else if(beforeNode == NULL && afterNode == NULL)
    {
        Add(freeList, allocAddress, allocSize, false);
        free(beforeNode);
        free(afterNode);
        return allocAddress; 
    }

    // coalesce with block before
    else if(beforeNode != NULL && afterNode == NULL)
    {
        beforeNode -> size += allocSize;
        allocAddress = beforeNode -> data;
        free(afterNode);
        return allocAddress;
    }
    return 0;
}

// Dump Memory List - Free
void DumpFree()
{
    if (freeList == NULL)
    {
        printf("Free List is Empty\n\n");
        return;
    }
    printf("Free List:\n");
    printList(freeList);
}

// Dump Memory List - Busy
void DumpBusy()
{
    if (busyList == NULL)
    {
        printf("Busy List is Empty\n\n");
        return;
    }
    printf("Busy List:\n");
    printList(busyList);
}

// Destroy Memory Manager - clear both lists
void DestroyMem()
{
    // free list and blocks
    Clear(freeList);
    Clear(busyList);
    freeList = NULL;
    busyList = NULL;
    printf("Memory Manager Destroyed Successfully\n");
}