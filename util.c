#include "stractgarbage.h"
#include "header.h"
#include <stdlib.h>



extern gc_t *gc;
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
	free_gc(gc);
	free_stack(heah_list);
	exit(EXIT_FAILURE);
}
