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
* add_dnodeint - add node to the fromm of the list
* @head: head
* @n: head
*
* Return: newNode
*/

stack_t *add_dnodeint(stack_t **head, const int n)
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