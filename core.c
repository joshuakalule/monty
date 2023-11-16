#include "monty.h"

static instruction_t ops[] = {
	{"push", _push},
	{"pall", _pall},
	{"pint", _pint},
	{"pop", _pop},
	{"swap", _swap},
	{"add", _add},
	{"nop", NULL},
	{"sub", _sub},
	{"div", _div},
	{"mul", _mul},
	{"mod", _mod},
	{"pchar", _pchar},
	{"pstr", _pstr},
	{"rotl", _rotl},
	{"rotr", _rotr},
	{"stack", NULL},
	{"queue", NULL},
	{NULL, NULL}
};

/**
 * get_instruction - tokenize the instructions on the line
 * @line: line from file
 * @code: pointer to code
 * @arg: pointer to arg
 */
void get_instruction(char *line, char *code, char *arg)
{
	char *token;
	char *delim = " \t\n";
	int n = 1;

	if (!line || !code || !arg)
		return;
	token = strtok(line, delim);
	while (token)
	{
		if (n == 1)
			strcpy(code, token);
		else if (n == 2)
			strcpy(arg, token);
		else
			break;
		n++;
		token = strtok(NULL, delim);
	}
}

/**
 * check_arg - check if the argument is valid
 * @arg: argument
 * Return: 0 (Success) | -1 (Fail)
 */
int check_arg(char *arg)
{
	unsigned int i;

	if (!*arg)
		return (-1);
	for (i = 0; arg[i] != '\0'; i++)
	{
		if (arg[i] == '-' && i == 0)
			continue;
		if (isdigit(arg[i]) == 0)
			return (-1);
	}
	return (0);
}

/**
 * execute - execute the instructions
 * @code: code
 * @arg: arg
 * @line_no: line number
 * @stack: pointer to pointer to the stack
 * @mode: mode of operations
 */
void execute(char *code, char *arg, int line_no, stack_t **stack, char *mode)
{
	unsigned int i, error = 0;
	(void)arg;

	if (!*code && !*arg)
		return;
	if (code[0] == '#')
		return;
	/*printf("'%s' '%s'\n", code, arg);*/
	for (i = 0; ops[i].opcode != NULL; i++)
	{
		if (strcmp(code, ops[i].opcode) == 0)
		{
			if (ops[i].f)
				ops[i].f(stack, line_no);
			break;
		}
	}
	if (!ops[i].opcode)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_no, code);
		error = 1;
	}
	else if (execute_2(code, arg, line_no, stack, mode) == -1)
	{
		error = 1;
	}

	if (error == 1)
	{
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}
/**
 * execute_2 - helper for execute
 * @code: code
 * @arg: argument
 * @line_no: line number
 * @stack: pointer to pointer to the stack
 * @mode: mode of operations
 *
 * Return: 0 (Success) | -1 (Failure)
 */
int execute_2(char *code, char *arg, int line_no, stack_t **stack, char *mode)
{
	int top;

	if (strcmp(code, "push") == 0)
	{
		if (check_arg(arg) == -1)
		{
		fprintf(stderr, "L%u: usage: push integer\n", line_no);
		return (-1);
		}
		(*stack)->n = atoi(arg);
		if (*mode == 'q')
			_rotl(stack, line_no);
	}
	else if (strcmp(code, "pchar") == 0)
	{
		top = (*stack)->n;
		if (top < 32 || top > 126)
		{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_no);
		return (-1);
		}
		fprintf(stdout, "%c\n", top);
	}
	else if (strcmp(code, "stack") == 0)
	{
		if (*mode != 's')
			*mode = 's';
	}
	else if (strcmp(code, "queue") == 0)
	{
		if (*mode != 'q')
			*mode = 'q';
	}
	return (0);
}
