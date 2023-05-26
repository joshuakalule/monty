#include "monty.h"

/**
 * _pop - removes the top element of the stack
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 */
void _pop(stack_t **stack, unsigned int line_no)
{
	stack_t *node;

	if (!stack)
		return;
	if (!*stack)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	node = *stack;
	free(*stack);
	(*stack) = node->next;
	if (node->next)
		node->next->prev = NULL;
}
