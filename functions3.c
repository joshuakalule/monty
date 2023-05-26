#include "monty.h"

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
