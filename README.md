# Memory-Manager

# Usage
Group Project: 3 Members

This project implements the stack, queue, and linked list data structures in the C language and makes them available to our operating system components.

# Installation
Ensure that all files are in the same folder. Enter the file the project is in.  From there, compile it by using gcc (filename) (filename) -o (test file name.exe).  Run the program by using ./(test file name.exe). 

# Dependencies
- math.h
- stdbool.h
- stdio.h
- stdlib.h
- project1.h

# Linked List
The Linked List is a generic data structure that grows and shrinks dynamically. It is implemented with a series of individually allocated nodes that point from one item to the next, in a specified order. Nodes can be added and inserted arbitrarily in O(1) time if a link to the insertion/deletion point is known ahead of time. Searching a linked-list is an O(n) operation.

Our Linked List Library implements a doubly-linked list that tracks pointers for the head and tail of the list, which point to the first and last node, respectively.

- typedef struct node
- typedef struct LLIST
- LLIST* CreateList()
- void* Add(LLIST* list, void* data, int size, bool cleanup)
- NODE* WalkToIndex(LLIST* list, int index)
- int IndexOf(LLIST* list, void* data, int startAtIndex)
- bool Contains(LLIST* list, void* data)
- void InsertBefore(LLIST* list, void* data, void* dataTarget, int size, bool cleanup)
- void InsertAfter(LLIST* list, void* data, void* dataTarget, int size, bool cleanup)
- void Insert(LLIST* list, void* data, int index, int size, bool cleanup)
- void RemoveNode(LLIST* list, void* data)
- void RemoveAt(LLIST* list, int index)
- void Clear(LLIST* list)
- void printList(LLIST* list)
- void SortList(LLIST* list)
