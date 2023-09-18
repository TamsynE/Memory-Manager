/*
Linked List
Adds, inserts, removes, and sorts individually allocated nodes in a doubly-linked list.
file: ll.c
author: Tamsyn Evezard
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "project1.h"

// CREATE LIST
LLIST* CreateList()
{
    LLIST* list = malloc(sizeof(LLIST));
    list -> head = NULL;
    list -> tail = NULL;
    list -> count = 0;

    return list;
};

// ADD NODE TO "END" OF LIST
void* Add(LLIST* list, void* data, int size, bool cleanup)
{
    NODE* curr = (NODE*)malloc(sizeof(NODE));
    curr -> data = data;
    curr -> size = size;
    curr -> cleanup = cleanup;

    // add to end of list
    if(list -> count > 0)
    {
        curr -> prev = list -> tail;
        list -> tail -> next = curr;
        list -> tail = curr;
        curr -> next = NULL;
        list -> count++;
    }
    // add to beginning
    else if(list -> count == 0)
    {
        list -> head = curr;
        curr -> prev = NULL;
        curr -> next = NULL;
        list -> tail = curr;
        list -> count++;
    }
    return data;
}

// WALK TO NODE BY INDEX
NODE* WalkToIndex(LLIST* list, int index)
{
    if(index < 0 || index > list -> count)
    {
        printf("Index out of Range: the list is not that long");
    }
    NODE* curr = list -> head;

    for(int i = 0; i < index; i++)
    {
        curr = curr -> next;
    }
    return curr;
}

// FIND INDEX OF NODE
int IndexOf(LLIST* list, void* data, int startAtIndex)
{
    int idx = startAtIndex;
    NODE* curr = (NODE*)malloc(sizeof(NODE));
    curr = WalkToIndex(list, startAtIndex);
    while (curr != NULL)
    {
        if(curr -> data == data)
        {
            return idx;
        }

        curr = curr -> next;
        idx++;
    }
    return -1;
}

bool Contains(LLIST* list, void* data)
{
    if(IndexOf(list, data, 0) >= 0)
    {
        return true;
    }
    return false;
}

// INSERT DATA BEFORE TARGET VALUE
void InsertBefore(LLIST* list, void* data, void* dataTarget, int size, bool cleanup)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode -> cleanup = cleanup;
    newNode -> data = data;
    newNode -> size = size;

    int i = IndexOf(list, dataTarget, 0);

    // if first node in list
    if(list -> count == 0)
    {
        printf("List is empty: Data added to beginning of list.\n");
        Add(list, data, size, cleanup);
    }

    // inserting before first node
    else if(i == 0)
    {
        newNode -> next = list -> head;
        list -> head -> prev = newNode;
        newNode -> prev = NULL;
        list -> head = newNode;
        list -> count++;
    }

    // inserting before nodes within the list
    else if(i > 0 && i <= list -> count)
    {
        NODE* nodePrev = WalkToIndex(list, i -1);
        NODE* nodeAfter = WalkToIndex(list, i);

        nodePrev -> next = newNode;
        newNode -> prev = nodePrev;
        newNode -> next = nodeAfter;
        nodeAfter -> prev = newNode;

        list -> count++;
    }
    
    else if(i < 0 || i > list -> count)
    {
        printf("The list cannot have values inputted at this index\n");
        return;
    }

}

// INSERT DATA AFTER TARGET VALUE
void InsertAfter(LLIST* list, void* data, void* dataTarget, int size, bool cleanup)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode -> cleanup = cleanup;
    newNode -> data = data;
    newNode -> size = size;

    int i = IndexOf(list, dataTarget, 0);

    // if first node in list
    if(list -> count == 0)
    {
        printf("List is empty: Data added to beginning of list.\n");
        Add(list, data, size, cleanup);
    }

    // after last node
    else if(i == list -> count -1)
    {
        Add(list, data, size, cleanup);
    }

    // somewhere after node inside list (first to second last)
    else if (i >= 0 && i < list -> count)
    {
        NODE* nodePrev = WalkToIndex(list, i);
        NODE* nodeAfter = WalkToIndex(list, i + 1);

        nodePrev -> next = newNode;
        newNode -> prev = nodePrev;
        newNode -> next = nodeAfter;
        nodeAfter -> prev = newNode;

        list -> count++;
    }

    // out of bounds
    else if(i < 0 || i >= list -> count)
    {
        printf("The list cannot have values inputted at this index\n");
        return;
    }
}

void Insert(LLIST* list, void* data, int index, int size, bool cleanup)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode -> cleanup = cleanup;
    newNode -> data = data;
    newNode -> size = size;

    // first node in list
    if(list -> count == 0 && index == 0)
    {
        Add(list, data, size, cleanup);
    }

    // inserting before first node
    else if(index == 0)
    {
        newNode -> next = list -> head;
        list -> head -> prev = newNode;
        newNode -> prev = NULL;
        list -> head = newNode;
        list -> count++;
    }

    // inserting between nodes
    else if(index > 0 && index < list -> count)
    {
        NODE* nodePrev = WalkToIndex(list, index -1);
        NODE* nodeAfter = WalkToIndex(list, index);

        nodePrev -> next = newNode;
        newNode -> prev = nodePrev;
        newNode -> next = nodeAfter;
        nodeAfter -> prev = newNode;

        list -> count++;
    }

    // inserting at end of list
    else if(index == list -> count)
    {
        NODE* nodePrev = WalkToIndex(list, index-1);
        newNode -> prev = nodePrev;
        list -> tail -> next = newNode;
        list -> tail = newNode;
        list -> count++;
    }
    
    else if(index < 0 || index > list -> count)
    {
        printf("The list cannot have values inputted at this index\n");
        return;
    }

}

// REMOVE USING DATA
void RemoveNode(LLIST* list, void* data)
{
    if(!Contains(list, data))
    {
        printf("Error: This list does not contain that data.\n");
        return;
    }

    int index = IndexOf(list, data, 0);
    
    RemoveAt(list, index);

}

// REMOVE USING INDEX
void RemoveAt(LLIST* list, int index)
{
    NODE* node = WalkToIndex(list, index);

    // if removing only thing in list
    if(index == 0 && list -> count == 1)
    {
        list -> head = list -> tail = node = NULL;
    }
    // remove from beginning of list
    if(index == 0 && list -> count > 1)
    {
        //update head to be new head
        NODE* oldhead = list -> head;
        list -> head = list -> head -> next;
        //list -> head -> prev = NULL;
        // free oldhead data
        free(oldhead);
    }

    // remove from somewhere in the list
    else if(index > 0 && index < list -> count -1)
    {
        NODE* nodePrev = node -> prev;
        NODE* nodeAfter = node -> next;

        nodePrev -> next = nodeAfter;
        nodeAfter -> prev = nodePrev;
        // free node data
        free(node);
    }
    // remove from end of list
    else if(index == list -> count -1 && list -> count > 1)
    {
        node -> next = NULL;
        NODE* nodePrev = node -> prev;
        NODE* oldTail = list -> tail;
        list -> tail = nodePrev;
        nodePrev -> next = NULL;
        free(oldTail);
    }

    node = NULL;
    list -> count--;
    if(list -> count == 0)
    {
        list -> head = list -> tail = NULL;
    }
}

// DESTROY LIST
void Clear(LLIST* list)
{
    if(list -> count == 0)
    {
        free(list);
    }
    else
    {
        NODE* curr = list -> head;
        while(curr -> next != NULL)
        {
            NODE* next = curr -> next;
            if(curr -> cleanup == true)
            {
                free(curr -> data); // free data in each node
            }
        
            free(curr); // then free the node itself
            curr = next;
        }
    
        list -> tail = list -> head = NULL;
        list -> count = 0;
        free(list);
    }
    
}

// DUMP LIST (PRINT TO USER)
void printList(LLIST* list)
{
    NODE* curr = list -> head;
    while(curr  != NULL)
    {
        printf("Address: %d [%d]\n", (int)curr->data, curr -> size); // ***
        curr = curr -> next;
    }
    printf("\n");
}

// SORT LIST IN ASCENDING ORDER
void SortList(LLIST* list) 
{
    for(NODE* curr = list -> head; curr != NULL; curr = curr -> next)
    {
        NODE* minNode = curr;
        for(NODE* inner = curr; inner != NULL; inner = inner -> next)
        {
            if(inner -> data < minNode -> data)
            {
                minNode = inner;
            }
        }
        void* temp = minNode -> data;
        void* temp1 = curr -> data;
        minNode -> data = temp1;
        curr -> data = temp;
    }
}