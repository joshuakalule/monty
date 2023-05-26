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
	{NULL, NULL}
};

/**
 * get_instruction - tokenize the instructions on the line
 * @line: line from file
 * @opcode: pointer to opcode
 * @arg: pointer to arg
 */
void get_instruction(char *line, char *opcode, char *arg)
{
	char *token;
	char *delim = " \t\n";
	int n = 1;

	if (!line || !opcode || !arg)
		return;
	token = strtok(line, delim);
	while (token)
	{
		if (n == 1)
		{
			strcpy(opcode, token);
		}
		else if (n == 2)
		{
			strcpy(arg, token);
		}
		else
		{
			break;
		}
		n++;
		token = strtok(NULL, delim);
	}
	free(token);
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
 * @opcode: opcode
 * @arg: arg
 * @line_no: line number
 * @stack: pointer to pointer to the stack
 */
void execute(char *opcode, char *arg, int line_no, stack_t **stack)
{
	unsigned int i;
	(void)arg;

	if (!*opcode && !*arg)
		return;
	/*printf("'%s' '%s'\n", opcode, arg);*/
	for (i = 0; ops[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, ops[i].opcode) == 0)
		{
			if (ops[i].f)
				ops[i].f(stack, line_no);
			break;
		}
	}
	if (strcmp(opcode, "push") == 0)
	{
		if (check_arg(arg) == -1)
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_no);
			free_stack(stack);
			exit(EXIT_FAILURE);
		}
		(*stack)->n = atoi(arg);
	}
	if (!ops[i].opcode)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_no, opcode);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}
