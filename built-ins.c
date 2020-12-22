#include "monty.h"
#include "stractgarbage.h"
#include <stdio.h>
#include <stdlib.h>



/**
* mod - mod the top two elements of the stack.
* @stack: head of stack
* @line_nb: instruction
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
* @line_nb: instruction
*
* Return: void
*/
void pchar(stack_t **stack, unsigned int line_nb)
{
	stack_t *top = NULL;

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
* @line_nb: instruction
*
* Return: void
*/
void pstr(stack_t **stack, __attribute__((unused)) unsigned int line_nb)
{
	stack_t *top = NULL;

	top = *stack;
	while (top)
	{
		if (top->n > 32 && top->n < 127)
			printf("%c", top->n);
		else
			break;
		top = top->next;
	}
	printf("\n");

}


/**
* rotl - rotl The top element of the stack becomes the last one,
* and the second top element of the stack becomes the first one
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void rotl(stack_t **stack, __attribute__((unused)) unsigned int line_nb)
{
	stack_t *top = NULL;

	top = *stack;

	if (top)
	{
		add_stack_end(stack, top->n);
		delete_stack_at_index(stack, 0);
	}
}




/**
* rotr - The opcode rotr rotates the stack to the bottom.
* @stack: head of stack
* @line_nb: instruction
*
* Return: void
*/
void rotr(stack_t **stack, __attribute__((unused)) unsigned int line_nb)
{
	stack_t *current = NULL;
	int i = 0;
	int len = 0;

	current = *stack;
	len = stack_len(*stack);
	while (1)
	{
		if (!current)
			break;
		add_stack(stack, current->n);
		current = current->next;
		i++;
	}
	i *= 2;

	for (; i > len - 1; i--)
		delete_stack_at_index(stack, i);
}
