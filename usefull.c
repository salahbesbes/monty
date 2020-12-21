
#include "monty.h"



/**
* write_message - print an message at stderror
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
* is_number - check if it is a number
* @str: cahr *
*
* Return: void
*/
int is_number(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (isNum(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
