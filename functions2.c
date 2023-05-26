#include "monty.h"

/**
 * _sub - does a subtraction operation
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 *
 * Description: subtracts the top element of the stack from the second top
 * element of the stack
 */
void _sub(stack_t **stack, unsigned int line_no)
{
	stack_t *node1, *node2;
	unsigned int count;
	int sum;

	if (!stack)
		return;
	count = sum = 0;
	node1 = *stack;
	while (node1)
	{
		count++;
		if (count < 2)
		{
			node2 = node1;
			node1 = node1->next;
			continue;
		}
		sum = node1->n - node2->n;
		node1->n = sum;
		_pop(stack, line_no);
		break;
	}
	if (count < 2)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * _add - adds the top two elements of the stack
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 */
void _add(stack_t **stack, unsigned int line_no)
{
	stack_t *node1, *node2;
	unsigned int count, sum;

	if (!stack)
		return;
	count = 0;
	sum = 0;
	node1 = *stack;
	while (node1)
	{
		count++;
		if (count < 2)
		{
			node2 = node1;
			node1 = node1->next;
			continue;
		}
		sum = node1->n + node2->n;
		node1->n = sum;
		_pop(stack, line_no);
		break;
	}
	if (count < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * _swap - swaps the top two elements of the stack
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 */
void _swap(stack_t **stack, unsigned int line_no)
{
	stack_t *node1, *node2;
	unsigned int count;

	if (!stack)
		return;
	count = 1;
	node1 = *stack;
	while (node1)
	{
		if (count < 2)
		{
			node2 = node1;
			node1 = node1->next;
			count++;
			continue;
		}
		node2->next = node1->next;
		if (node1->next)
			node1->next->prev = node2;
		node2->prev = node1;
		node1->next = node2;
		node1->prev = NULL;
		*stack = node1;
		count++;
		break;
	}
	if (count <= 2)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}

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
	(*stack) = node->next;
	if (*stack)
		(*stack)->prev = NULL;
	free(node);
}
