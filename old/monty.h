#ifndef Gard
#define Gard


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define isAlpha(X) ((X >= 'A' && X <= 'Z') || (X >= 'a' && X <= 'z'))
#define isNotAlpha(X) ((X <= 'A' || X >= 'Z') && (X <= 'a' || X >= 'z'))
#define isNum(X) (X >= '0' && X <= '9')
#define isNotNum(X) (X < '0' || X > '9')


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
char *check_for_built_in(stack_t **head_list, line_t *inst);
void print_error(char *arg1, char *arg2, char *arg3, char *arg4);
int is_number(char *str);
char **create_ar_tokens(char **line);
int _ar_len(void **V);
void pint(stack_t **stack, line_t *line);
void pop(stack_t **stack, line_t *line);
void swap(stack_t **stack, line_t *line);
void add(stack_t **stack, line_t *line);
void sub(stack_t **stack, line_t *line);
void divv(stack_t **stack, line_t *line);
void mod(stack_t **stack, line_t *line);
void mul(stack_t **stack, line_t *line);
void nop(stack_t **stack, line_t *line);
void pchar(stack_t **stack, line_t *line);
void pstr(stack_t **stack, line_t *line);
void rotl(stack_t **stack, line_t *line);



#endif
