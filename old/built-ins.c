#include "monty.h"
#include "garbageCollector.h"
#include "stractgarbage.h"
#include <stdio.h>
#include <stdlib.h>




/**
* pint - print the value of the stack top
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void pint(stack_t **stack, __attribute__((unused))line_t *line)
{
	stack_t *current = NULL;

	current = *stack;
	while (current->next)
		current = current->next;
	printf("%d\n", current->n);
}


/**
* pop - free the top (tail) of the stack
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void pop(stack_t **stack, line_t *line)
{
	stack_t *current = NULL;
	char line_nb[15];

	current = *stack;

	if (!current)
	{
		sprintf(line_nb, "%d", line->idx);
		print_error("L", line_nb, ": can't pop an empty stack", "");
		__exit(*stack);
	}
	if (current && !current->next)
	{
		free(current);
		*stack = NULL;
		return;
	}
	while (current->next)
		current = current->next;

	current->prev->next = NULL;
	free(current);
}


/**
* swap - swaps the top two elements of the stack.
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void swap(stack_t **stack, line_t *line)
{
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

	if (!current)
	{
		print_error("L", line_nb, ": can't swap, stack too short", "");
		__exit(*stack);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		print_error("L", line_nb, ": can't swap, stack too short", "");
		__exit(*stack);
	}

	lastNode = current;
	beforeLast = current->prev;

	beforeLast->next = NULL;
	lastNode->next = beforeLast;
	lastNode->prev = beforeLast->prev;
	if (beforeLast->prev)
		beforeLast->prev->next = lastNode;
	beforeLast->prev = lastNode;

}

/**
* add - add the top two elements of the stack.
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void add(stack_t **stack, line_t *line)
{
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

	if (!current)
	{
		print_error("L", line_nb, ": can't add, stack too short", "");
		__exit(*stack);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		print_error("L", line_nb, ": can't add, stack too short", "");
		__exit(*stack);
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
void nop(stack_t **stack, __attribute__((unused))line_t *line)
{
	__exit(*stack);
}


/**
* sub - add the top two elements of the stack.
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void sub(stack_t **stack, line_t *line)
{
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

	if (!current)
	{
		print_error("L", line_nb, ": can't sub, stack too short", "");
		__exit(*stack);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		print_error("L", line_nb, ": can't sub, stack too short", "");
		__exit(*stack);
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
void divv(stack_t **stack, line_t *line)
{
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

	if (!current)
	{
		print_error("L", line_nb, ": can't div, stack too short", "");
		__exit(*stack);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		print_error("L", line_nb, ": can't div, stack too short", "");
		__exit(*stack);
	}

	lastNode = current;
	beforeLast = current->prev;
	if (lastNode->n == 0)
	{
		print_error("L", line_nb, ": division by zero", "");
		__exit(*stack);
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
void mul(stack_t **stack, line_t *line)
{
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

	if (!current)
	{
		print_error("L", line_nb, ": can't mul, stack too short", "");
		__exit(*stack);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		print_error("L", line_nb, ": can't mul, stack too short", "");
		__exit(*stack);
	}

	lastNode = current;
	beforeLast = current->prev;
	if (lastNode->n == 0)
	{
		print_error("L", line_nb, ": division by zero", "");
		__exit(*stack);
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
void mod(stack_t **stack, line_t *line)
{
	stack_t *current = NULL, *lastNode = NULL, *beforeLast = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

	if (!current)
	{
		print_error("L", line_nb, ": can't mod, stack too short", "");
		__exit(*stack);
	}

	while (current->next)
	{
		current = current->next;
		len++;
	}
	if (len < 2)
	{
		print_error("L", line_nb, ": can't mod, stack too short", "");
		__exit(*stack);
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
void pchar(stack_t **stack, line_t *line)
{
	stack_t *current = NULL, *lastNode = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

	if (!current)
	{
		print_error("L", line_nb, ": can't pchar, stack empty", "");
		__exit(*stack);
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
		print_error("L", line_nb,": can't pchar, value out of range","");
		__exit(*stack);
	}

}



/**
* pstr - pstr print all int as escii code
* @stack: head of stack
* @line: instruction
*
* Return: void
*/
void pstr(stack_t **stack, line_t *line)
{
	stack_t *current = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

	if (!current)
	{
		printf("\n");
		__exit(*stack);
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
*/
void rotl(stack_t **stack, line_t *line)
{
	stack_t *current = NULL, *firstNode = NULL, *top = NULL;
	char line_nb[15];
	int len = 1;

	current = *stack;
	sprintf(line_nb, "%d", line->idx);

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
