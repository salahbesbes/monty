#include "monty.h"
#include "stractgarbage.h"
#include <stdio.h>





/**
* pint - print the value of the stack top
* @stack: head of stack
* @line: instruction
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
* @line: instruction
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
* @line: instruction
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
* add - add the top two elements of the stack.
* @stack: head of stack
* @line: instruction
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
* @line: instruction
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
* @line: instruction
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
* @line: instruction
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
* @line: instruction
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

/**
* mod - mod the top two elements of the stack.
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void mod(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL, *NextTop = NULL;
	int len = 1;

	top = *stack;

	len = stack_len(*stack);
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_nb);
		__exit(*stack, 0);
	}

	if (top->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_nb);
		__exit(*stack, 0);
	}
	NextTop = top->next;
	NextTop->n %= top->n;
	NextTop->prev = NULL;
	*stack = NextTop;
	free(top);

}

/**
* pchar - pchar prit the escii code of the top node
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void pchar(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL, *NextTop = NULL;
	int len = 1;

	top = *stack;

	if (!top)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_nb);
		__exit(*stack, 0);
	}

	if (top->n > 32 && top->n < 127)
		printf("%c\n", top->n);
	else
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_nb);
		__exit(*stack, 0);
	}

}



/**
* pstr - pstr print all int as escii code
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void pstr(stack_t **stack, __attribute__((unused)) unsigned int line_nb)
{
	stack_t *top = NULL;

	top = *stack;
	while (top)
	{
		if ((top->n < 32 && top->n >= 127) || top->n == 0)
			break;
		else
			printf("%c", top->n);
		top = top->next;
	}
	printf("\n");

}


/**
* rotl - rotl The top element of the stack becomes the last one,
* and the second top element of the stack becomes the first one
* @stack: head of stack
* @line: instruction
*
* Return: void
void rotl(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL, *firstNode = NULL, *top = NULL;
	int len = 1;

	top = *stack;

	if (top && top->next)
	{
		firstNode = top;
		printf("f->n = %d\n", firstNode->n);
		while (top->next)
		{
			top = top->next;
			len++;
		}
		top = top;

	}
}
*/
