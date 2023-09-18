/*
Memory Manager Test Program
Tests Memory Manager 
file: mmtest.c
author: Tamsyn Evezard, Andie Perreira, Fatima Nava
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "project1.h"
#include "project2.h"

// Unit Test Program
int main()
{
    CreateMemoryManager(1000, false);

    // busyList:
    mallocMem(5, true); // 0-5
    mallocMem(5, true); // 5-10 -- 1
    mallocMem(5, true); // 10-15 -- 2
    mallocMem(5, true); // 15-20 -- 4
    mallocMem(5, true); // 20-25 -- 3

    // freeList after mallocMem: 25-1000 (975)
    DumpBusy();
    DumpFree();


    freeMem((void*)5); // no colescing
    freeMem((void*)10); // coalesce with block before
    freeMem((void*)20); // coalesce with block after
    freeMem((void*)15);  // coalesce with before and after 
    
    //freeList after freeMem: 5-1000 (995)
    DumpBusy();
    DumpFree();

    DestroyMem();

    // should have nothing in both lists
    DumpBusy();
    DumpFree();

    return 0;
}