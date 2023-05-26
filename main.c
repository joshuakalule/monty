#include "monty.h"

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
