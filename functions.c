#include "monty.h"

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
