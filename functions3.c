#include "monty.h"

/**
 * _pstr - prints the strings in the stack
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 *
 * Description: prints the string starting at the top of the stack
 * followed by a new line
 */
void _pstr(stack_t **stack, unsigned int line_no)
{
	stack_t *node;
	int n;
	(void) line_no;

	if (!stack)
	{
		fprintf(stdout, "\n");
		return;
	}
	node = *stack;
	while (node)
	{
		n = node->n;
		if (n == 0)
			break;
		if (n < 32 || n > 126)
			break;
		fprintf(stdout, "%c", n);
		fflush(stdout);
		node = node->next;
	}
	fprintf(stdout, "\n");
}

/**
 * _mod - performs a modulo operation
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 *
 * Description: computes the rest of the division of the second top element
 * of the stack by the top element of the stack
 */
void _mod(stack_t **stack, unsigned int line_no)
{
	stack_t *node1, *node2;
	unsigned int count;
	int modulo;

	if (!stack)
		return;
	count = 0;
	node1 = *stack;
	while (node1)
	{
		count++;
		if (count == 1 && node1->n == 0)
		{
		fprintf(stderr, "L%d: division by zero\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
		}
		else if (count < 2)
		{
		node2 = node1;
		node1 = node1->next;
		continue;
		}
		modulo = node1->n % node2->n;
		node1->n = modulo;
		_pop(stack, line_no);
		break;
	}
	if (count < 2)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * _mul - performs a multiplication operation
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 *
 * Description: multiplies the second top element of the stack
 * with the top element of the stack
 */
void _mul(stack_t **stack, unsigned int line_no)
{
	stack_t *node1, *node2;
	unsigned int count;
	int multiple;

	if (!stack)
		return;
	count = 0;
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
		multiple = node1->n * node2->n;
		node1->n = multiple;
		_pop(stack, line_no);
		break;
	}
	if (count < 2)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}

/**
 * _div - does a division operation
 * @stack: pointer to pointer to the stack
 * @line_no: line number
 *
 * Description: divides the second top elemnt of the stack by the
 * top element of the stack
 */
void _div(stack_t **stack, unsigned int line_no)
{
	stack_t *node1, *node2;
	unsigned int count;
	int quo;

	if (!stack)
		return;
	count = 0;
	node1 = *stack;
	while (node1)
	{
		count++;
		if (count == 1 && node1->n == 0)
		{
		fprintf(stderr, "L%d: division by zero\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
		}
		if (count < 2)
		{
		node2 = node1;
		node1 = node1->next;
		continue;
		}
		quo = node1->n / node2->n;
		node1->n = quo;
		_pop(stack, line_no);
		break;
	}
	if (count < 2)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_no);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}
