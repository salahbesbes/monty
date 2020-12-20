#ifndef Gard
#define Gard


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/**
 * struct line_s - content of the line and its indx
 * @command: command name
 * @arg: argument
 * @idx: nb of the line
 */
typedef struct line_s
{
	char *command;
	char *arg;
	int idx;
} line_t;




/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, line_t *line);
} instruction_t;


int _puts(char *str);
int _putchar(char c);
int _len(void **V);
void __exit(stack_t *head_list);
int str_is_eq(char *str1, char *str2);
void check_for_built_in(stack_t **head_list, line_t *inst);


#endif
