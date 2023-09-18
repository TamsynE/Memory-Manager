#ifndef project1_h
#define project1_h

#include <stdbool.h>

typedef struct node
{
    void* data;
    int size;
    struct node* prev;
    struct node* next;
    bool cleanup;
}NODE;

typedef struct
{
    NODE* head;
    int count;
}QUEUE;

typedef struct
{
    NODE* head;
    NODE* tail;
    int count;
}LLIST;

LLIST* CreateList();

void* Add(LLIST* list, void* data, int size, bool cleanup);
NODE* WalkToIndex(LLIST* list, int index);
int IndexOf(LLIST* list, void* data, int startAtIndex);
bool Contains(LLIST* list, void* data);
void InsertBefore(LLIST* list, void* data, void* dataTarget, int size, bool cleanup);
void InsertAfter(LLIST* list, void* data, void* dataTarget, int size, bool cleanup);
void Insert(LLIST* list, void* data, int index, int size, bool cleanup);
void RemoveNode(LLIST* list, void* data);
void RemoveAt(LLIST* list, int index);
void Clear(LLIST* list);
void printList(LLIST* list);
void SortList(LLIST* list);

void enqueue(QUEUE* queue, void* temp);
void* dequeue(QUEUE* q);
bool isEmpty(QUEUE* q);
void dumpQueue(QUEUE* q);

void* Push(LLIST* s, void* data, int size);
void Pop(LLIST* s);
void dumpStack(LLIST* s);
void DestroyStack(LLIST* s);
bool isStackEmpty(LLIST* s);

#endif