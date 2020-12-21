#include "stractgarbage.h"
#include "garbageCollector.h"
#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



extern gc_t *gc;
extern FILE *stream_ptr;
extern char *line_ptr;


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
* func -  function
* @argc: nb of args
*
* Return: void
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
* @prevLength: length of the old array
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
* create_ar_tokens - create an array of string of all args in the line
* @line: adress of the pointer line
*
* Return: array of strings
*/
char **create_ar_tokens(char **line)
{
	void **ar_tokens = NULL;
	char *token = NULL;
	int i = 1;

	/* parse instruction into token and save them to struct */
	while (i)
	{
		/* since we insert int into gc we cant move the pointer line as we want */
		token = parse_line(line);
		if (!token) /* we dont want args more than 1 */
			break;
		token = copy_obj(strlen(token) + 1, token);
		ar_tokens = insertToLastPosion(ar_tokens, token);
		i++;
	}

	_ar_len(ar_tokens);
	/*
	if (length < 1 && length > 2)
		return (NULL);
	else if (length == 2 && !is_number(ar_tokens[1]))
		return (NULL);
	else
	*/
	return ((char **) ar_tokens);

}

/**
 * str_is_eq - compare two given strings and see if they are the same
 * @str1: first string
 * @str2: second string
 *
 * Return: 1 if both strings are equale and 0 if not
 */
int str_is_eq(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else
			return (0);
	}
	if (*str1 != '\0' || *str2 != '\0')
		return (0);
	return (1);
}



/**
* free_stack - free_stack
* @head: head
*
* Return: void
*/
void free_stack(stack_t *head)
{
	if (head)
	{
		while (1)
		{
			if (head->prev)
			{
				free(head->prev);
			}
			if (!(head->next))
			{
				free(head);
				break;
			}
			head = head->next;
		}
	}
}




/**
* __exit - exit the program, free all gc pointers, close the stream
* @msg: message to print to stderr
* @arg: argument
*
* Return: void
*/
void __exit(stack_t *heah_list)
{

	if (stream_ptr)
		fclose(stream_ptr);
	if (line_ptr)
		free(line_ptr);
	free_gc(gc);
	free_stack(heah_list);
	exit(EXIT_FAILURE);
}
