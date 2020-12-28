#include "monty.h"
#include "stractgarbage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

line_t *instruction = NULL;

/**
 * __exit - exit adn free gc and stack adn close stream
 * @head_list: head_list
 * @status: status of exit
 *
 * Return: void
 */
void __exit(stack_t *head_list, int status)
{

	free_stack(head_list);

	free(instruction->getlinePtr);
	if (instruction->stream)
		fclose(instruction->stream);
	free_gc(gc);
	if (status)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}


/**
* treat_one_line -  function
* @head_list: head_list
* @line: char *
*
* Return: int
*/
int treat_one_line(stack_t **head_list, char *line)
{
	char *ret = NULL;
	int res = 0;

	instruction->command = strtok(line, " \n\t\r\a");
	if (!instruction->command)
		return (2);
	else if (instruction->command && instruction->command[0] != '#')
	{
		instruction->arg = strtok(NULL, " \n\t\r\a");
		ret = check_for_built_in(head_list);
		if (!ret)
			__exit(*head_list, 0);
	}
	return (res);
}

/**
* init_instruction - init_instruction
* Return: void
*/
void init_instruction(void)
{

	instruction->arg = NULL;
	instruction->command = NULL;
	instruction->getlinePtr = NULL;
	instruction->stream = NULL;

}
/**
* read_file - treat every line of the file
* @head_list: head_list
*
* Return: void
*/
void read_file(stack_t **head_list)
{
	char *line = NULL, *newLine = NULL;
	size_t len = 0;
	ssize_t nread = 0;
	unsigned int idxLine = 1;

	while (idxLine)
	{
		nread = getline(&line, &len, instruction->stream);
		instruction->getlinePtr = line;
		if (nread == -1)
			break;
		instruction->idx = idxLine;
		idxLine++;
		newLine = copy_obj(strlen(line) + 1, line);
		treat_one_line(head_list, newLine);
	}
	__exit(*head_list, 1);
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
	FILE *stream = NULL;
	char *filename = NULL;
	stack_t *head_list = NULL;

	if (argc != 2)
	{
		print_error("USAGE: monty file", "", "", "");
		exit(EXIT_FAILURE);
	}
	instruction = create_obj(sizeof(line_t));
	if (!instruction)
	{
		print_error("Error: malloc failed", "", "", "");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	init_instruction();
	stream = fopen(filename, "r");
	if (!stream)
	{
		print_error("Error: Can't open file ", filename, "", "");
		__exit(head_list, 0);
	}
	instruction->stream = stream;

	read_file(&head_list);
	return (0);
}
