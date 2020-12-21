#include "monty.h"
#include "garbageCollector.h"

#include <stdio.h>
#include <stdlib.h>


/**
* pall - print the stack
* @stack: head_list
* @line_number: idx of the line
*
* Return: void
*/
void pall(stack_t **stack, __attribute__((unused)) line_t *line)
{
	const stack_t *current = NULL;

	current = *stack;
	if (!current)
		__exit(*stack);
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
void push(stack_t **stack, line_t *line)
{
	stack_t *newNode = NULL, *current = NULL;
	char nb_line[15];

	current = *stack;
	if (!line->arg || !is_number(line->arg))
	{
		sprintf(nb_line, "%d", line->idx);
		print_error("L", nb_line, ": usage: push integer", "");
		__exit(*stack);
	}
	newNode = malloc(sizeof(stack_t));
	if (!newNode)
	{
		print_error("Error: malloc failed", "", "", "");
		return;
	}
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
	char nb_line[15];

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
		{"rotl", rotl},
		{NULL, NULL}
	};
	for (i = 0; exec[i].opcode && inst->command; i++)
	{
		found = str_is_eq(exec[i].opcode, inst->command);
		if (found)
		{
			return (exec[i].f);
		}
	}

	sprintf(nb_line, "%d", inst->idx);
	if (!found)
		print_error("L", nb_line, ": unknown instruction ", inst->command);
	return (NULL);
}

/**
* check_for_built_in - check if the built-in exist run it
* @inst: struct instruction
*
* Return: void
*/
char *check_for_built_in( stack_t **head_list, line_t *inst)
{
	void (*builtin_func)(stack_t **stack, line_t *line);

	builtin_func = get_builtin_func(inst);
	if (builtin_func)
	{
		builtin_func(head_list, inst);
		return ("OK");
	}
	return (NULL);
}
