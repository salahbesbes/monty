#include "monty.h"


/**
* pint - print the value of the stack top
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void pint(stack_t **stack, __attribute__((unused))unsigned int line_nb)
{
	stack_t *top = NULL;

	top = *stack;
	if (!top)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_nb);
		__exit(*stack, 0);
	}
	printf("%d\n", top->n);
}

/**
* pop - free the top (tail) of the stack
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void pop(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL;

	top = *stack;

	if (!top)
	{

		fprintf(stderr, "L%u: can't pop an empty stack\n", line_nb);
		__exit(*stack, 0);
	}
	if (top && !top->next)
	{
		free(top);
		*stack = NULL;
		return;
	}

	*stack = top->next;
	(*stack)->prev = NULL;
	free(top);
}



/**
* swap - swaps the top two elements of the stack.
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void swap(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL;
	int len = 0, valTop = 0, valNextTop = 0;

	top = *stack;

	len = stack_len(*stack);
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_nb);
		__exit(*stack, 0);
	}
	valTop = top->n;
	valNextTop = top->next->n;

	delete_stack_at_index(stack, 0);
	delete_stack_at_index(stack, 0);
	add_stack(stack, valTop);
	add_stack(stack, valNextTop);
}

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
