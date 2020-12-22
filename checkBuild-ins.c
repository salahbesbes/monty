#include "monty.h"
#include "stractgarbage.h"

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
	const stack_t *current = NULL;

	current = *stack;
	if (!current)
		return;
	while (current->next)
		current = current->next;
	while (current)
	{
		printf("%d\n", current->n);
		current = current->prev;
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
	stack_t *newNode = NULL, *current = NULL;

	current = *stack;
	if (!instruction->arg || !is_number(instruction->arg))
	{
		print_error("L", instruction->idx, ": usage: push integer", "");
		__exit(*stack);
	}
	newNode = malloc(sizeof(stack_t));
	if (!newNode)
	{
		print_error("Error: malloc failed", "", "", "");
		__exit(*stack);
	}
	newNode->n = atoi(instruction->arg);
	newNode->next = NULL;

	if (!*stack)
	{
		newNode->prev = NULL;
		*stack = newNode;
		return;
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
}


/**
* get_builtin_func - check for the right function by checking the given command
* name and frol a list of predefined functions
* @inst: pointer to a struct instruction
*
* Return: void function(**stack_t, unsigned int idx)
* Error: NULL
*/
void (*get_builtin_func())(stack_t**, unsigned int )
{
	int i = 0, found = 0;

	instruction_t exec[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"divv", divv},
		{"sub", sub},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		/*
		{"rotl", rotl},
		*/
        {NULL, NULL}
	};
	for (i = 0; exec[i].opcode && instruction->command; i++)
	{
		found = str_is_eq(exec[i].opcode, instruction->command);
		if (found)
		{
			return (exec[i].f);
		}
	}

	if (!found)
		print_error("L", instruction->idx, ": unknown instruction ", instruction->command);
	return (NULL);
}

/**
* check_for_built_in - check if the built-in exist run it
* @inst: struct instruction
*
* Return: void
*/
char *check_for_built_in(stack_t **head_list)
{
	void (*builtin_func)(stack_t **stack, unsigned int line_number);

	builtin_func = get_builtin_func();
	if (builtin_func)
	{
		builtin_func(head_list, atoi(instruction->idx));
		return ("OK");
	}
	return (NULL);
}
