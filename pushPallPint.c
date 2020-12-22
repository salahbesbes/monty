#include "monty.h"

extern line_t *instruction;
extern gc_t *gc;

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

extern line_t *instruction;
extern gc_t *gc;
/**
* pall - print the stack
* @stack: head_list
* @line_number: idx of the line
*
* Return: void
*/
void pall(stack_t **stack,  __attribute__((unused)) unsigned int line_number)
{
	const stack_t *current = *stack;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
/**
* push - push to the stack
* @stack: head_list
* @line_number: idx of the line
*
* Return: void
*/
void push(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	stack_t *newNode = NULL;
    int n = 0;

	if (!instruction->arg || !is_number(instruction->arg))
	{
		fprintf(stderr, "L%s: usage: push integer\n", instruction->idx);
		__exit(*stack, 0);
	}
	n = atoi(instruction->arg);
	newNode = add_dnodeint(stack, n);
	if (!newNode)
	{
		fprintf(stderr, "Error: malloc faile\n");
		__exit(*stack, 0);
	}

}
