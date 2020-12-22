#include "monty.h"
#include <stdio.h>


extern line_t *instruction;



/**
* pint - print the value of the stack top
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void pint(stack_t **stack, __attribute__((unused))unsigned int line_nb)
{
	stack_t *current = NULL;

	current = *stack;
	if (!current)
		fprintf(stderr, "L%u: can't pint, stack empty", line_nb);
	printf("%d\n", current->n);
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
	stack_t *current = NULL;

	current = *stack;

	if (!current)
	{

		fprintf(stderr, "L%u: can't pop an empty stack", line_nb);
		__exit(*stack, 0);
	}
	if (current && !current->next)
	{
		free(current);
		*stack = NULL;
		return;
	}

	*stack = current->next;
	(*stack)->prev = NULL;
	free(current);
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
	stack_t *current = NULL, *top = NULL, *beforetop = NULL;

	current = *stack;

	if (!current)
	{

		fprintf(stderr, "L%u: can't pop an empty stack", line_nb);
		__exit(*stack, 0);
	}

	top = current;
	beforetop = current->next;

	beforetop->prev = NULL;
	top->prev = beforetop;
	top->next = beforetop->next;
	if (beforetop->next)
		beforetop->next->prev = top;
	beforetop->next = top;

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
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	int len = 1;

	current = *stack;

	if (!current)
	{

		fprintf(stderr, "L%u: can't pop an empty stack", line_nb);
		__exit(*stack, 0);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't pop an empty stack", line_nb);
		__exit(*stack, 0);
	}

	lastNode = current;
	beforeLast = current->prev;

	beforeLast->n += lastNode->n;
	beforeLast->next = NULL;
	free(lastNode);

}



/**
* nop - dont do any thing
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void nop(stack_t **stack, __attribute__((unused))unsigned int line_nb)
{
	__exit(*stack, 0);
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
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	int len = 1;

	current = *stack;

	if (!current)
	{
		fprintf(stderr, "L%u: can't pop an empty stack", line_nb);
		__exit(*stack, 0);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't pop an empty stack", line_nb);
		__exit(*stack, 0);
	}

	lastNode = current;
	beforeLast = current->prev;

	beforeLast->n -= lastNode->n;
	beforeLast->next = NULL;
	free(lastNode);

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
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	int len = 1;

	current = *stack;

	if (!current)
	{
		fprintf(stderr, "L%u: can't pop an empty stack", line_nb);
		__exit(*stack, 0);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't pop an empty stack", line_nb);
		__exit(*stack, 0);
	}

	lastNode = current;
	beforeLast = current->prev;
	if (lastNode->n == 0)
	{
		fprintf(stderr, "L%u: division by zero", line_nb);
		__exit(*stack, 0);
	}
	beforeLast->n /= lastNode->n;
	beforeLast->next = NULL;
	free(lastNode);

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
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	int len = 1;

	current = *stack;

	if (!current)
	{
		fprintf(stderr, "L%u: division by zero", line_nb);
		__exit(*stack, 0);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%u: division by zero", line_nb);
		__exit(*stack, 0);
	}

	lastNode = current;
	beforeLast = current->prev;
	if (lastNode->n == 0)
	{
		fprintf(stderr, "L%u: division by zero", line_nb);
		__exit(*stack, 0);
	}
	beforeLast->n *= lastNode->n;
	beforeLast->next = NULL;
	free(lastNode);

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
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	int len = 1;

	current = *stack;

	if (!current)
	{
		fprintf(stderr, "L%u: division by zero", line_nb);
		__exit(*stack, 0);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%u: division by zero", line_nb);
		__exit(*stack, 0);
	}

	lastNode = current;
	beforeLast = current->prev;

	beforeLast->n %= lastNode->n;
	beforeLast->next = NULL;
	free(lastNode);

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
	stack_t *current = NULL, *lastNode = NULL;
	int len = 1;

	current = *stack;

	if (!current)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty", line_nb);
		__exit(*stack, 0);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}

	lastNode = current;
	if (lastNode->n > 32 && lastNode->n < 127)
		printf("%c\n", lastNode->n);
	else
	{
		fprintf(stderr, "L%u: can't pchar, value out of range", line_nb);
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
	stack_t *current = NULL;
	int len = 1;

	current = *stack;

	if (!current)
	{
		printf("\n");
		__exit(*stack, 0);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	while (current)
	{
		if ((current->n < 32 && current->n >= 127) || current->n == 0)
			break;
		else
			printf("%c", current->n);
		current = current->prev;
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
	stack_t *current = NULL, *firstNode = NULL, *top = NULL;
	int len = 1;

	current = *stack;

	if (current && current->next)
	{
		firstNode = current;
		printf("f->n = %d\n", firstNode->n);
		while (current->next)
		{
			current = current->next;
			len++;
		}
		top = current;

	}
}
*/
