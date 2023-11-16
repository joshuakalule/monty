#include "monty.h"
/**
 * _pchar - prints the char at the top of the stack
 * @stack: pointer to pointer to stack
 * @line_number: line number
 */
void _pchar(stack_t **stack, unsigned int line_number)
{
	if (!stack)
		return;
	if (!*stack)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * _pint - prints the value at the top of the stack
 * @stack: pointer to pointer to stack
 * @line_number: line number
 */
void _pint(stack_t **stack, unsigned int line_number)
{
	if (!stack)
		return;
	if (!*stack)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "%d\n", (*stack)->n);
}

/**
 * _push - push an element onto the stack
 * @stack: stack
 * @line_number: line number
 */
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

/**
 * _pall - print all elements on the stack
 * @stack: stack
 * @line_number: line number
 */
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
