#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "garbageCollector.h"


FILE *stream_ptr = NULL;
char *line_ptr = NULL;

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
 * trim_instruction - trim string
 * @inst: instruction
 * @delim: delimitation
 *
 * Return: char *
 */
char *trim_instruction(char *inst, char *delim)
{
	char *newStr = NULL, *current = NULL;
	int i = 0, idxEnd = 0, j = 0;

	current = inst;
	while (*current)
	{
		for (j = 0; delim[j]; j++)
		{
			while (*current == delim[j])
			{
				current++;
				j = 0;
			}
		}
		break;
	}
	if (current[i] == '\0')
	{
		destroy_obj(inst);
		return (NULL);
	}
	while (current[i])
	{
		if (isAlpha(current[i]) || isNum(current[i]))
			idxEnd = i + 1;
		i++;
	}
	current[idxEnd] = '\0';

	newStr = copy_obj(strlen(current) + 1, current);
	destroy_obj(inst);
	return (newStr);

}

/**
* check_for_comment - eliminate any comments
* @str: string
*
* Return: char *
*/
char *check_for_comment(char *str)
{
	char *newStr = NULL;
	int i = 0;

	if (!str || str[i] == '#')
		return (NULL);

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '#' && isAlpha(str[i - 1]))
			continue;
		else if (str[i] == '#' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			str[i] = '\0';
			break;
		}
	}
	newStr = copy_obj(strlen(str) + 1, str);
	destroy_obj(str);
	return (newStr);
}

/**
* core_program - handle all treatment of the line we get
* @line: str
* @idxLine: last ch of the string
* @head_list: head_list
*
* Return: line
*/
char *core_program(char *line, int idxLine, stack_t **head_list)
{
	int istoken = 1;
	char *token = NULL, *res = NULL;
	line_t *instruction = NULL;

	instruction = create_obj(sizeof(line_t));
	instruction->command = NULL;
	instruction->arg = NULL;
	instruction->idx = idxLine;

	line = check_for_comment(line);
	if (!line || *line == '\0')
		return (NULL);
	line = trim_instruction(line, " \t\n");

	if (!line || *line == '\0')
		return (NULL);
	else if (*line == '\0')
		return ("");

	/* parse instruction into token and save them to struct */
	while (istoken)
	{
		/* since we insert int into gc we cant move the pointer line as we want */
		token = parse_line(&line);
		if (!token || istoken > 2) /* we dont want args more than 1 */
			break;
		token = copy_obj(strlen(token) + 1, token);
		if (istoken == 1)
			instruction->command = token;
		if (istoken == 2)
			instruction->arg = token;
		istoken++;
	}

	res = check_for_built_in(head_list, instruction);
	return (res);
}
/**
* read_file - read instruction line from a file
* @filename: filename
* @head_list: head_list
*
* Return: 0
* Error: -1
*/
int read_file(char *filename, stack_t **head_list)
{
	FILE *stream = NULL;
	char *line = NULL, *newLine = NULL, *res = NULL;
	size_t len = 0, idxLine = 0;
	ssize_t nread = 0;

	if (!filename)
	{
		print_error("Error: Can't open file ", filename, "", "");
		__exit(*head_list);
	}
	stream = fopen(filename, "r");
	if (!stream)
	{
		print_error("Error: Can't open file ", filename, "", "");
		__exit(*head_list);
	}
	stream_ptr = stream;
	while (1)
	{

		fflush(stdin);
		fflush(stream);
		nread = getline(&line, &len, stream);
		line_ptr = line;
		idxLine++;
		if (nread == -1)
			break;
		/**
		 * we dont want to touch the line any more we made ou own copy
		 * becase of the logic of getline()
		 */
		if (!line || line[0] == '\n' || line[0] == '#')
			continue;
		newLine = copy_obj(strlen(line) + 1, line);
		res = core_program(newLine, idxLine, head_list);
		if (!res)
		{
			__exit(*head_list);
		}
		else if (*res == '\0')
			continue;

	}
	__exit(*head_list);
	return (EXIT_SUCCESS);
}

/**
* main - main function
* @argc: nb of args
* @argv: arguments
*
* Return: 0
* Error: -1
*/
int main(int argc, char *argv[])
{
	stack_t *head_list = NULL;


	if (argc != 2)
	{
		print_error("USAGE: monty file", "", "", "");
		exit(EXIT_FAILURE);
	}

	read_file(argv[1], &head_list);

	return (0);
}
