#include "monty.h"

/**
 * _rotl - rotates the stack to the top
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 */
void _rotl(stack_t **stack, unsigned int line_no)
{
	stack_t *node1, *node2;
	(void)line_no;

	if (!stack || !*stack)
		return;
	node1 = *stack;
	while (node1->next)
		node1 = node1->next;
	node2 = (*stack)->next;
	if (node2)
	{
		node1->next = *stack;
		(*stack)->prev = node1;
		(*stack)->next = NULL;
		*stack = node2;
	}
}

/**
  * _rotr - rotates the stack to the bottom
  * @stack: pointer to pointer to the stack
  * @line_no: line number
  */
void _rotr(stack_t **stack, unsigned int line_no)
{
	stack_t *node1, *node2;
	(void)line_no;

	if (!stack || !*stack)
		return;
	node1 = *stack;
	while (node1->next)
		node1 = node1->next;
	node2 = (*stack)->next;
	if (node2)
	{
		node1->next = *stack;
		(*stack)->prev = node1;
		node1->prev->next = NULL;
		node1->prev = NULL;
		*stack = node1;
	}
}

