#include "monty.h"

#define MALLOC_FAILED fprintf(stderr, "Error: malloc failed\n")
#define OPCODE_SIZE 1024
#define ARG_SIZE 1024

void free_stack(stack_t **stack)
{
	stack_t *node, *next_node;

	if (!stack)
		return;
	node = *stack;
	while (node)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
	/*free(stack);*/
}
	

int get_instruction(char *line, char *opcode, char *arg)
{
	char *token;
	char *delim = " \t\n";
	int n = 1;

	if (!line || !opcode || !arg)
		return (-1);
	token = strtok(line, delim);
	while (token && n <= 2)
	{
		if (n == 1)
		{
			strcpy(opcode, token);
		}
		if (n == 2)
		{
			strcpy(arg, token);
		}
		n++;
		token = strtok(NULL, delim);
	}
	free(token);
	return (0);
}

void _push(stack_t **stack, unsigned int line_number)
{
	stack_t *new;
	(void)line_number;

	if (!stack)
		return;
	new = malloc(sizeof(stack_t));
	if (!new)
	{
		MALLOC_FAILED;
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	new->prev = NULL;
	new->next = *stack;
	if (*stack)
		(*stack)->prev = new;
	*stack = new;
}

void _pall(stack_t **stack, unsigned int line_number)
{
	stack_t *node;
	(void)line_number;

	if (!stack)
		return;
	node = *stack;
	while (node)
	{
		fprintf(stdout, "%d\n", node->n);
		node = node->next;
	}
}

instruction_t list[] = {
	{"push", _push},
	{"pall", _pall},
	{NULL, NULL}
};

int check_arg(char *arg, unsigned int line_no)
{
	unsigned int i;

	for (i = 0; arg[i] != '\0'; i++)
	{
		if (arg[i] == '-' && i == 0)
			continue;
		if (isdigit(arg[i]) == 0)
		{
			fprintf(stderr, "L%u: push integer\n", line_no);
			return (-1);
		}
	}
	return (0);
}


void execute(char *opcode, char *arg, int line_no, stack_t **stack)
{
	unsigned int i;
	(void)arg;

	for (i = 0; list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, list[i].opcode) == 0)
		{
			if (list[i].f)
				list[i].f(stack, line_no);
			break;
		}
	}
	
	if (!list[i].opcode)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_no, opcode);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	
	if (strcmp(opcode, "push") == 0)
	{
		if (check_arg(arg, line_no) == -1)
		{
			free_stack(stack);
			exit(EXIT_FAILURE);
		}
		(*stack)->n = atoi(arg);
	}
}

/**
 * main - entry point
 * @argc:  number of arguments passed
 * @argv: argument list
 *
 * Return: 0 (SUCCESS)
 */
int main(int argc, char **argv)
{
	char *filepath;
	char line[BUFSIZE];
	FILE *fp;
	unsigned int line_no = 1;
	stack_t *stack = NULL;
	char opcode[OPCODE_SIZE] = {'\0'};
	char arg[ARG_SIZE] = {'\0'};

	if (argc != 2)
	{
		fprintf(stderr, "Usage: monty file\n");
		exit(EXIT_FAILURE);
	}
	
	filepath = argv[1];
	fp = fopen(filepath, "r"); 
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filepath);
		exit(EXIT_FAILURE);
	}
	
	while (fgets(line, BUFSIZE, fp))
	{

		/*printf("[%i]: %s", line_no, line);*/
		get_instruction(line, opcode, arg);
		/*printf("opcode: %s arg: %s\n", opcode, arg);*/
		execute(opcode, arg, line_no, &stack);
		line_no++;
		memset(opcode, '\0', sizeof(opcode));
		memset(arg, '\0', sizeof(arg));
	}

	fclose(fp);
	free_stack(&stack);
	return (0);
}
