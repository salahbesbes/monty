#include "monty.h"

/**
* stack_len - get length
* @h: head
*
* Return: int
*/
size_t stack_len(const stack_t *h)
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
* add_stack - add node to the fromm of the list
* @head: head
* @n: head
*
* Return: newNode
*/

stack_t *add_stack(stack_t **head, const int n)
{
	stack_t *newNode = NULL;

	newNode = malloc(sizeof(stack_t));
	if (!newNode)
		return (NULL);

	newNode->n = n;
	newNode->prev = NULL;
	newNode->next = *head;
	if (*head)
		(*head)->prev = newNode;
	*head = newNode;
	return (newNode);

}

/**
* insert_stack_at_index - insert_stack_at_index
* @h: head
* @idx: index
* @n: data
*
* Return: head
*/
stack_t *insert_stack_at_index(stack_t **h, unsigned int idx, int n)
{
	stack_t *current = NULL, *newNode = NULL, *prev = NULL;
	unsigned int i = 0;

	current = *h;
	if (idx == 0)
		return (add_stack(h, n));
	while (current && i < idx)
	{
		prev = current;
		current = current->next;
		i++;
	}
	if (i == idx && !current)
		return (add_stack_end(h, n));

	if (idx > i)
		return (NULL);
	newNode = malloc(sizeof(stack_t));
	if (!newNode)
		return (NULL);
	newNode->n = n;
	newNode->prev = prev;
	newNode->next = current;
	prev->next = newNode;
	current->prev = newNode;
	return (newNode);
}


/**
* delete_stack_at_index - delete_stack_at_index
* @head: head
* @index: index
*
* Return: 1 / 0
*/

int delete_stack_at_index(stack_t **head, unsigned int index)
{
	stack_t *current = NULL, *prev = NULL, *Next = NULL;
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
/**
* add_stack_end - add at the end if the list
* @head: head of the list
* @n: data
*
* Return: 1
*/
stack_t *add_stack_end(stack_t **head, const int n)
{
	stack_t *newNode = NULL, *current = NULL;

	current = *head;
	newNode = malloc(sizeof(stack_t));
	if (!newNode)
		return (NULL);
	newNode->n = n;
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
