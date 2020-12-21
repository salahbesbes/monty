#include "monty.h"
#include "stractgarbage.h"
#include <stdio.h>
#include <string.h>

extern line_t *instruction;
extern gc_t *gc;
/**
* _ar_len - get the length of an array of something
* @V: array
*
* Return: length
*/
int _ar_len(void **V)
{
	int len = 0;

	if (V)
	{
		while (V[len])
			len++;
	}
	return (len);
}



/**
* insertToLastPosion - create newptr allocate length + 1, copy all content for
* the old one insert the pointer sent to the last mostition
* @ptr: array of pointer
* @str: pointer to add to last position
* @gc: gc
*
* Return: void
*/

void **insertToLastPosion(void **ptr, void *str)
{
	void **newAllocation = NULL;
	int i = 0, prevLength = _ar_len(ptr);
	int size = sizeof(char *) * (prevLength + 2);


	newAllocation = create_obj(size);

	if (prevLength == 0)
	{
		newAllocation[prevLength] = str;
		newAllocation[1] = NULL;
		return (newAllocation);
	}

	for (i = 0; i < prevLength; i++)
		newAllocation[i] = ptr[i];

	newAllocation[i] = str;
	newAllocation[i + 1] = NULL;

	destroy_obj(ptr);
	return (newAllocation);
}

/**
* parse_line - parse an instruction by one or more char in the string
* @instruction: instruction of line
*
* Return: char
*/
char *parse_line(char **instruction)
{
	char *token = NULL;

	if (!instruction || !*instruction)
		return (NULL);
	token = *instruction;
	if (token[0] == '\0')
		return (NULL);
	while (**instruction)
	{
		if (**instruction == ' ' || **instruction == '\t')
		{
			**instruction = '\0';
			while (isNotAlpha(**instruction) && isNotNum(**instruction))
				(*instruction)++;
			break;
		}
		*instruction += 1;
	}

	return (token);
}
/**
* create_args - create an array of arguments
* @line: char*
* @gc: gc
*
* Return: char**
*/
char **create_args(char *line)
{
	void **ar_tokens = NULL;
	char *token = NULL;

	while (1)
	{
		token = parse_line(&line);
		if (!token)
			break;
		token = copy_obj(strlen(token) + 1, token);
		ar_tokens = insertToLastPosion(ar_tokens, token);
	}

	return ((char **)ar_tokens);

}

/**
 * create_struct_instruction - define the global var instruction
 * ar_tokens: array of string
 * idx: line_nb
 *
 * Return: void
 */
void create_struct_instruction(char **ar_tokens)
{


	instruction->command = ar_tokens[0];
	instruction->arg = ar_tokens[1];


}
