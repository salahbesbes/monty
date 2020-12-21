
#include "stractgarbage.h"
#include <stdio.h>
#include <stdlib.h>

/**
* print_gc - print list
* @h: header
*
* Return: nb of element found
*/
size_t print_gc(const gc_t *h)
{
	const gc_t *current = NULL;
	size_t count = 0;

	if (!h)
		return (count);
	current = h;
	while (current)
	{
		printf("(%ld) = %p\n", count, current->garbage);
		current = current->next;
		count++;
	}
	return (count);
}


/**
* gc_len - get length
* @h: head
*
* Return: int
*/
size_t gc_len(const gc_t *h)
{
	size_t count = 0;

	if (h)
	{
		while (h)
		{
			count++;
			h = h->next;
		}
	}
	return (count);
}



/**
* add_garbage - add node to the fromm of the list
* @head: head
* @garbage: garbage ptr
*
* Return: newNode
*/

gc_t *add_garbage(gc_t **head, void *garbage)
{
	gc_t *newNode = NULL;

	newNode = malloc(sizeof(gc_t));
	if (!newNode)
		return (NULL);

	newNode->garbage = garbage;
	newNode->prev = NULL;
	newNode->next = *head;
	if (*head)
		(*head)->prev = newNode;
	*head = newNode;
	return (newNode);

}



/**
* add_garbage_end - add at the end if the list
* @head: head of the list
* @garbage: garbage ptr
*
* Return: head of list
*/
gc_t *add_garbage_end(gc_t **head, void *garbage)
{
	gc_t *newNode = NULL, *current = NULL;

	current = *head;
	newNode = malloc(sizeof(gc_t));
	if (!newNode)
		return (NULL);
	newNode->garbage = garbage;
	newNode->next = NULL;

	if (!*head)
	{
		newNode->prev = NULL;
		*head = newNode;
		return (*head);
	}
	while (1)
	{
		if (current->next == NULL)
		{
			current->next = newNode;
			newNode->prev = current;
			break;
		}
		current = current->next;
	}
	return (*head);
}



/**
* free_gc - free_gc
* @head: head
*
* Return: void
*/
void free_gc(gc_t *head)
{
	if (head)
	{
		while (1)
		{
			if (head->prev)
			{
				free(head->prev->garbage);
				free(head->prev);
			}
			if (!(head->next))
			{
				free(head->garbage);
				free(head);
				break;
			}
			head = head->next;
		}
	}
}


/**
* get_garbage_at_index - get_garbage_at_index
* @head: head
* @index: position
*
* Return: head
*/
gc_t *get_garbage_at_index(gc_t *head, unsigned int index)
{
	unsigned int i = 0;
	gc_t *current = NULL;

	current = head;

	while (i <= index && current)
	{
		if (i == index)
			return (current);
		current = current->next;
		i++;
	}

	return (current);

}


/**
* insert_garbage_at_index - insert_garbage_at_index
* @h: head
* @idx: index
*
* Return: head
*/
gc_t *insert_garbage_at_index(gc_t **h, unsigned int idx, void *garbage)
{
	gc_t *current = NULL, *newNode = NULL, *prev = NULL;
	unsigned int i = 0;

	current = *h;
	if (idx == 0)
		return (add_garbage(h, garbage));
	while (current && i < idx)
	{
		prev = current;
		current = current->next;
		i++;
	}
	if (i == idx && !current)
		return (add_garbage_end(h, garbage));

	if (idx > i)
		return (NULL);
	newNode = malloc(sizeof(gc_t));
	if (!newNode)
		return (NULL);
	newNode->garbage = garbage;
	newNode->prev = prev;
	newNode->next = current;
	prev->next = newNode;
	current->prev = newNode;
	return (newNode);
}


/**
* delete_garbage_at_index - delete_garbage_at_index
* @head: head
* @index: index
*
* Return: 1 / 0
*/

int delete_garbage_at_index(gc_t **head, unsigned int index)
{
	gc_t *current = NULL, *prev = NULL, *Next = NULL;
	unsigned int i = 0;

	if (!*head)
		return (-1);
	current = *head, prev = (*head)->prev, Next = current->next;
	if (index == 0 && Next)
	{
		*head = Next;
		(*head)->prev = NULL;
		free(current);
		return (1);
	}
	else if (index == 0 && !Next)
	{
		*head = NULL;
		free(current);
		return (1);
	}

	while (current && i <= index)
	{
		if (i == index)
		{
			prev->next = Next;
			if (Next)
				Next->prev = prev;
			free(current);
			break;
		}
		prev = current;
		current = current->next;
		if (current)
			Next = current->next;
		i++;
	}

	if (index > i)
		return (-1);
	return (1);
}
