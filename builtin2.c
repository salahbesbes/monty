#include "monty.h"

/**
* add - add the top two elements of the stack.
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void add(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL, *NextTop = NULL;
	size_t len = 0;

	top = *stack;

	len = stack_len(*stack);
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_nb);
		__exit(*stack, 0);
	}

	NextTop = top->next;

	NextTop->n += top->n;
	NextTop->prev = NULL;
	*stack = NextTop;
	free(top);

}



/**
* nop - dont do any thing
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void nop(__attribute__((unused)) stack_t **stack,
		__attribute__((unused))unsigned int line_nb)
{

}


/**
* sub - add the top two elements of the stack.
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void sub(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL, *NextTop = NULL;
	int len = 1;

	top = *stack;

	len = stack_len(*stack);
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_nb);
		__exit(*stack, 0);
	}

	NextTop = top->next;

	NextTop->n -= top->n;
	NextTop->prev = NULL;
	*stack = NextTop;
	free(top);

}


/**
* divv - div the top two elements of the stack.
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void divv(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL, *NextTop = NULL;
	int len = 1;

	top = *stack;

	len = stack_len(*stack);
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_nb);
		__exit(*stack, 0);
	}

	if (top->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_nb);
		__exit(*stack, 0);
	}
	NextTop = top->next;
	NextTop->n /= top->n;
	NextTop->prev = NULL;
	*stack = NextTop;
	free(top);

}


/**
* mul - mul the top two elements of the stack.
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void mul(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL, *NextTop = NULL;
	int len = 1;

	top = *stack;

	len = stack_len(*stack);
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_nb);
		__exit(*stack, 0);
	}
	NextTop = top->next;
	NextTop->n *= top->n;
	NextTop->prev = NULL;
	*stack = NextTop;
	free(top);

}
