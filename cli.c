/*
Memory Manager CLI Program
User Interface for Memory Manager
file: cli.c
author: Tamsyn Evezard, Andie Perreira, Fatima Nava
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "project1.h"
#include "project2.h"

int main( int argc, char *argv[] )  
{
    printf("Welcome to the Memory Manager! \nPlease enter the size of your manager.\n");
    int sizeTotal;
    int bestFit;
    int option;
    bool bf;
    int size;
    int data;

    printf("Memory Manager Size: \n");
    scanf("%d", &sizeTotal);
    printf("Your Memory Manager has a size of: %d\n", sizeTotal);

    printf("Which memory allocation technique would you like to use?\n");
    printf("Input '1' for first-fit OR '2' for best-fit allocation: \n");
    scanf("%d", &bestFit);
    
    if(bestFit == 1)
    {
        bf = false;
        printf("Your Memory Manager is allocating using first-fit\n");
    }

    else if(bestFit == 2)
    {
        bf = true;
        printf("Your Memory Manager is allocating using best-fit\n");
    }

    else
    {
        printf("ERROR: Input should be <1> or <2>. Please re-run program.\n");
        return 0;
    }
    
    printf("\n");
    CreateMemoryManager(sizeTotal, bf); 
    
    printf("Options: \n1: Allocate Memory \n2: Deallocate Memory \n3: Dump Free List \n4: Dump Busy List \n5: Destroy Memory Manager\n0: QUIT\n");
    scanf("%d", &option); 
    
    while(option == 1 || option == 2 || option == 3 || option == 4 || option == 5)
    {
        printf("\n");
        if(option == 1)
        {
            printf("How much memory do you want to allocate?\n");
            scanf("%d", &size);
            mallocMem(size, bf);
        }

        else if(option == 2)
        {
            printf("Which memory block do you want to deallocate? Please provide the address:\n");
            scanf("%d", &data);
            void* dataaa = (void*)data;
            freeMem(dataaa);
        }
        
        else if(option == 3)
        {
            DumpFree(); 
        }

        else if(option == 4)
        {
            DumpBusy();
        }

        else if(option == 5)
        {
            DestroyMem();
        }

        printf("Options: \n1: Allocate Memory \n2: Deallocate Memory \n3: Dump Free List \n4: Dump Busy List \n5: Destroy Memory Manager\n0: QUIT\n");
        scanf("%d", &option);
    }

    if(option == 0)
    {
        printf("Goodbye\n");
        return 0;
    }

    else if (option != 1 || option != 2 || option != 3 || option != 4 || option != 5 || option != 0)
    {
        printf("ERROR: That was not an option, please enter a number between 1-5\n");
        return 0;
    }
    return 0;
}