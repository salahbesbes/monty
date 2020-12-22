#include "monty.h"





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
		fprintf(stderr, "L%u: unknown instruction %s\n", instruction->idx, instruction->command);
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
		builtin_func(head_list, instruction->idx);
		return ("OK");
	}
	return (NULL);
}
