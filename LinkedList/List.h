#pragma once
#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>


// Define a structure for linked list elements.

typedef struct ListElement_ {
	void * data;
	struct ListElement_ * next;
} ListElement;

// Define a structure for Linked list.

typedef struct List_ {
	int size;
	int  (*match)(const void *key1, const void *key2);
	void(*destroy)(void *data);

	ListElement *head;
	ListElement *tail;

} List;

// Prototypes to be used in the program

void list_init(List * list, void (*destroy)(void *data));  //initializes a linked list so that it can be used in other operations

void list_destroy(List * list);  //destroys a linked list, obviously.

int list_insert_next(List * list, ListElement * element, const void * data);   // inserts an element into a linked list just after a specified element

int list_remaining_next(List * list, ListElement * element, void ** data);   // removes an element from linked list just after a specified element.


// these macros provides an interface for accessing and testing members of List and ListElement structures.


#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define list_data(element) ((element)->data)

#define list_next(element) ((element)->next)



#endif // !_LIST_H
