# Memory-Manager

# Usage
Group Project: 3 Members

This project implements a Memory Manager in the C language, using the Linked List library.

The Memory Manager library starts with a single node in a memory map list (a linked list) that accounts for the entire block of memory that is available.

Using a configuration file, the memory manager can run in either First-Fit or Best-Fit modes. It tracks memory allocations using a Busy List and a Free List. When users request a memory allocation, the Memory Manager will identify an appropriate block from the Free List and return a pointer to its base address. It tracks blocks so that every request is given its own unique block that does not conflict with any other allocations. As blocks are deallocated, they coalesce to form the largest blocks possible and avoid fragmentation.

# Installation
Ensure that all files are in the same folder. Enter the file the project is in.  

Compiling and running the Memory Manager Test Program:
- gcc ll.c mm.c mmtest.c -o mm.exe  
- ./mm.exe

Compiling and running the Command Line Program:
- gcc ll.c mm.c cli.c -o cli.exe
- ./cli.exe

# Dependencies
- include <math.h>
- include <stdio.h>
- include <stdlib.h>
- include <stdbool.h>
- include "project1.h"
- include "project2.h"

# Memory Manager
- void CreateMemoryManager(int sizeTotal, bool bf)
- void* mallocMem(int size, bool bf)
- NODE* CheckBusyList(void* data)
- NODE* CheckFreeListBefore(NODE* curr)
- NODE* CheckFreeListAfter(NODE* curr)
- void* freeMem(void* data)
- void DumpFree()
- void DumpBusy()
- void DestroyMem()


# Command Line Program
The command line program allows a user to simulate an operating system. 

The program has commands for:
- allocating by size
- freeing by address
- printing busy list
- printing free list
- destroying memory manager
