#include <stdlib.h>
#include <string.h>

#include "List.h"

// list_init

void list_init(List * list, void(*destroy)(void *data))
{
	//initializes the list

	list->size = 0;
	list->destroy = destroy;
	list->head = ((void *)0);
	list->tail = ((void *)0);
	return;
}

//destroy

void list_destroy(List * list)
{
	void * data;

	while (list_size(list) > 0)
	{
		if (list_remaining_next(list, NULL, (void **)&data) == 0 && list->destroy != ((void *)0))
		{
			list->destroy(data);
		}
	}

	//clear as good to do it
	memset(list, 0, sizeof(List));

	return;
}

int list_insert_next(List * list, ListElement * element, const void * data)
{
	ListElement * new_element; //inserted

	//Allocate storage like a kind fellow you are.

	if ((new_element = (ListElement *)malloc(sizeof(ListElement))) == ((void *)0))  // i know I should just use NULL, but I like showing off.
	{
		return -1;
	}

	//insert the element

	new_element->data = (void *)data;

	if (element == ((void *)0) )
	{
		if (list_size(list) == 0)
		{
			list->tail = new_element;
		}
		new_element->next = list->head;
		list->head = new_element;
	}
	else
	{
		//insert it anywhere else other than head.
		if (element->next == ((void *)0))
		{
			list->tail = new_element;
		}
		new_element->next = element->next;
		element->next = new_element;
	}
	//adjust size to account the newly inserted element else the newly added element would feel shy
	list->size++;
	return 0;
}

int list_remaining_next(List * list, ListElement * element, void ** data)
{
	ListElement * old_element;

	//do not allow removal from an empty list

	if (list_size(list) == 0)
	{
		return -1;
	}

	if (element == ((void *)0))
	{
		//handles removal from head of the list
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1)
		{
			list->tail = NULL;
		}
	}
	else
	{
		//handle removal somewhere else other than head.

		if (element->next == NULL)
		{
			return -1;
		}
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;
		if (element->next == NULL)
		{
			list->tail = element;
		}
	}
	free(old_element);

	//Again adjust size after removing an element;
	list->size--;
	
	return 0;
}