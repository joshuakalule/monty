#include "monty.h"

FILE *efp = NULL;

/**
 * free_stack - frees the stack
 * @stack: pointer to pointer to stack
 */
void free_stack(stack_t **stack)
{
	stack_t *node, *next_node;

	if (!stack || !*stack)
		return;
	node = *stack;
	while (node)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
	/* close the open file */
	if (efp)
		fclose(efp);
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
	char mode = 's'; /* s - stack (default), q - queue */

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	filepath = argv[1];
	fp = fopen(filepath, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filepath);
		exit(EXIT_FAILURE);
	}
	/* set external variable */
	efp = fp;
	while (fgets(line, BUFSIZE, fp))
	{
		/*printf("[%i]: %s", line_no, line);*/
		get_instruction(line, opcode, arg);
		/*printf("opcode: %s arg: %s\n", opcode, arg);*/
		execute(opcode, arg, line_no, &stack, &mode);
		line_no++;
		memset(opcode, '\0', sizeof(opcode));
		memset(arg, '\0', sizeof(arg));
	}

	fclose(fp);
	efp = NULL;
	free_stack(&stack);
	return (0);
}
