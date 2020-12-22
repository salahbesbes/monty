#include "monty.h"



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
* print_error - print an message at stderror
* @arg1: msg
* @arg2: msg
* @arg3: msg
* @arg4: msg
*
* Return: void
*/
void print_error(char *arg1, char *arg2, char *arg3, char *arg4)
{
	fprintf(stderr, "%s", arg1);
	fprintf(stderr, "%s", arg2);
	fprintf(stderr, "%s", arg3);
	fprintf(stderr, "%s", arg4);
	fprintf(stderr, "\n");

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
* is_number - check if it is a number
* @str: cahr *
*
* Return: void
*/
int is_number(char *str)
{
	int i = 0;

	if (str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (isNum(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
