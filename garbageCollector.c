#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "garbageCollector.h"
#include "stractgarbage.h"
#include "header.h"
gc_t *gc;

/**
* copy_obj - allocate and copy string
* @size: size to allocate
* @ptr: ptr to coppy
*
* Return: new pointer to allocated string
*/

void *copy_obj(size_t size, void *ptr)
{

	size_t i = 0;
	char *newPtr;
	char *str = (char *) ptr;

	if (!ptr)
		return (NULL);

	newPtr = malloc(size);

	if (!newPtr)
		return (NULL);
	for (i = 0; i < size - 1; i++)
	{
		newPtr[i] = str[i];
	}
	newPtr[i] = '\0';

	add_garbage(&gc, newPtr);
	return (newPtr);
}
/**
* create_obj - allocate a single pointer
* @size: size to be allocated
*
* Return: newPtr
*/
void *create_obj(size_t size)
{
	void *newPtr = NULL;

	if (size)
	{
		newPtr = malloc(size);
		add_garbage(&gc, newPtr);
	}
	return (newPtr);
}


/**
* destroy_obj - search for the pointer and free it
* @ptr: pointer to be deleted
*
* Return: void
*/

void destroy_obj(void *ptr)
{
	int idx = 0;
	gc_t *current = gc;


	while (current)
	{
		if (current->garbage == ptr)
			break;
		current = current->next;
		idx++;
	}

	if (idx == 0)
	{
		gc = current->next;
		if (gc)
			gc->prev = NULL;
		free(ptr);
		free(current);
		return;
	}
	else if (current) /* if we did not found  current == NULL */
	{
		current->prev->next = current->next;
		if (current->next)
			current->next->prev = current->prev;
		free(ptr);
		free(current);

	}

}

/**
* destroy_all - destroy_all content of the garbege collector
*
* Return: void
*/
void destroy_all(void)
{
	free_gc(gc);
}
