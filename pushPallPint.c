#include "monty.h"


/**
* pall - print the stack
* @stack: head_list
* @line_number: idx of the line
*
* Return: void
*/
void pall(stack_t **stack, unsigned int line_number)
{
	const stack_t *current = *stack;

	(void)line_number;
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
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newNode = NULL;
	int n = 0;

	if (!instruction->arg || !is_number(instruction->arg))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		__exit(*stack, 0);
	}
	n = atoi(instruction->arg);
	newNode = add_stack(stack, n);
	if (!newNode)
	{
		fprintf(stderr, "Error: malloc faile\n");
		__exit(*stack, 0);
	}

}
