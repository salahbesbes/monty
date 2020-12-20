#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "garbageCollector.h"


#define isAlpha(X) ((X >= 'A' && X <= 'Z') || (X >= 'a' && X <= 'z'))
#define isNotAlpha(X) ((X <= 'A' || X >= 'Z') && (X <= 'a' || X >= 'z'))
#define isNum(X) (X >= '0' && X <= '9')
#define isNotNum(X) (X < '0' || X > '9')


FILE *stream;
char *getlineStr;


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
	//printf("0000token = %s\n", token);
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

	//printf("token = %s\n", token);
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
		free(inst);
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
* chech_format - check the order of the command and arg
* @line: char *
*
* Return: 1
* Error: 0
*/
int chech_format(char *line, stack_t *head_list)
{
	if (!line || isNum(*line))
	{
		__exit(head_list);
		return (0);
	}
	else
		return (1);
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
	int istoken = 0;
	char *token = NULL;
	line_t *instruction = NULL;

	/*
	*/
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
	istoken = chech_format(line, *head_list); /* i = 1 or 0 */
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
	if (istoken == 0)
		printf("first arg in int \n");
	else
	{
		check_for_built_in(head_list, instruction);
		/*
		printf("com = %s\n", instruction->command );
		printf("arg = %s\n", instruction->arg );
		printf("idxLine = %d\n", instruction->idx );
		printf(" \n"  );
		*/
	}

	return (NULL);
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
	char *line = NULL, *newLine = NULL;
	size_t len = 0;
	int nread = 0;
	int idxLine = 0;
	if (!filename)
		__exit(*head_list);
	stream = fopen(filename, "r");
	stream = stream;
	if (!stream)
		__exit(*head_list);
	while (1)
	{
		fflush(stdin);
		fflush(stream);
		nread = getline(&line, &len, stream);
		getlineStr = line; /* we save the last getline into gc */
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
		core_program(newLine, idxLine, head_list);
	}
	free(line);
	fclose(stream);
	__exit(*head_list);
	return (nread);
}

/**
* main - main function
* @argc: nb of args
* @argv: arguments
*
* Return: 0
* Error: -1
*/
int main(__attribute__((unused)) int argc,__attribute__((unused)) char *argv[])
{
	stack_t *head_list = NULL;

	read_file("./test1.m", &head_list);

	return (0);
}
