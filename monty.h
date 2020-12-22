#ifndef Gard
#define Gard
#include "stractgarbage.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define isAlpha(X) ((X >= 'A' && X <= 'Z') || (X >= 'a' && X <= 'z'))
#define isNotAlpha(X) ((X <= 'A' || X >= 'Z') && (X <= 'a' || X >= 'z'))
#define isNum(X) (X >= '0' && X <= '9')
#define isNotNum(X) (X < '0' || X > '9')



/**
 * struct line_s - content of the line and its indx
 * @command: command name
 * @arg: argument
 * @idx: nb of the line
 * @getlinePtr: last getline pointer to be freed
 * @stream: the stream opened
 */
typedef struct line_s
{
	char *command;
	char *arg;
	unsigned int idx;
	char *getlinePtr;
	FILE *stream;
} line_t;

extern gc_t *gc;
extern line_t *instruction;


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
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void print_error(char *arg1, char *arg2, char *arg3, char *arg4);
char *format_line(char *line);
void free_stack(stack_t *head);
char **create_args(char *line);
void create_struct_instruction(char **ar_tokens);
char *check_for_built_in( stack_t **head_list);
int is_number(char *str);
int str_is_eq(char *str1, char *str2);
void __exit(stack_t *head_list, int status);


stack_t *add_dnodeint(stack_t **head, const int n);
size_t stack_len(const stack_t *h);
/*
int _puts(char *str);
int _putchar(char c);
int _len(void **V);
void __exit(stack_t *head_list);
int str_is_eq(char *str1, char *str2);
char *check_for_built_in(stack_t **head_list, line_t *inst);
int is_number(char *str);
char **create_ar_tokens(char **line);
int _ar_len(void **V);
*/
void pint(stack_t **stack, unsigned int line_number);
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void sub(stack_t **stack, unsigned int line_number);
void divv(stack_t **stack, unsigned int line_number);
void mod(stack_t **stack, unsigned int line_number);
void mul(stack_t **stack, unsigned int line_number);
void nop(stack_t **stack, unsigned int line_number);
void pchar(stack_t **stack, unsigned int line_number);
void pstr(stack_t **stack, unsigned int line_number);
void rotl(stack_t **stack, unsigned int line_number);


#endif
