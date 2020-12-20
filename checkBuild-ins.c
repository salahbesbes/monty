#include "header.h"
#include <stdlib.h>



/**
* pall - print the stack
* @stack: head_list
* @line_number: idx of the line
*
* Return: void
*/
void pall(stack_t **stack, __attribute__((unused))line_t *line)
{
	const stack_t *current = NULL;

	current = *stack;
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
void push(stack_t **stack, line_t *line)
{



	stack_t *newNode = NULL, *current = NULL;

	current = *stack;
	newNode = malloc(sizeof(stack_t));
	//if (!newNode)
	//	return (NULL);
	newNode->n = atoi(line->arg);
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



	/*
*/
}


/**
* get_builtin_func - check for the right function by checking the given command
* name and frol a list of predefined functions
* @inst: pointer to a struct instruction
*
* Return: void function(**stack_t, unsigned int idx)
* Error: NULL
*/
void (*get_builtin_func(line_t *inst))(stack_t**, line_t *)
{
	int i = 0, found = 0;
	instruction_t exec[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
	};
	for (i = 0; exec[i].opcode && inst->command; i++)
	{
		found = str_is_eq(exec[i].opcode, inst->command);
		if (found)
			return (exec[i].f);
	}

	return (NULL);
}

/**
* check_for_built_in - check if the built-in exist run it
* @inst: struct instruction
*
* Return: void
*/
void check_for_built_in( stack_t **head_list, line_t *inst)
{
	void (*builtin_func)(stack_t **stack, line_t *line);

	builtin_func = get_builtin_func(inst);
	if (builtin_func)
	{
		builtin_func(head_list, inst);
	}
}
