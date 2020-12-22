#include "monty.h"
#include "stractgarbage.h"


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

	if (!inst)
	{
		destroy_obj(inst);
		return (NULL);
	}
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
		return ("");
	while (current[i])
	{
		if (current[i] >= 32 && current[i] <= 126)
			idxEnd = i + 1;
		i++;
	}
	current[idxEnd] = '\0';

	newStr = copy_obj(strlen(current) + 1, current);
	destroy_obj(inst);
	return (newStr);

}
/**
* format_line - trim line
* @line: char *
*
* Return: char *
*/
char *format_line(char *line)
{
	char *newLine = NULL;

	newLine = trim_instruction(line, " \t");
	return (newLine);
}
