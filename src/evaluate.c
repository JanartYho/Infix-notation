#include "evaluate.h"

#include <math.h>	 // ✅ Используем pow() для `^`
#include <stdio.h>
#include <stdlib.h>

bool evaluate_rpn(TokenList *rpn, int *result)
{
	int *stack = malloc(rpn->size * sizeof(int));
	if (!stack)
		return false;

	int stack_size = 0;

	for (int i = 0; i < rpn->size; i++)
	{
		Token token = rpn->tokens[i];

		if (token.type == 'n')
		{
			stack[stack_size++] = token.value;
		}
		else
		{
			if (stack_size < 2)
			{
				free(stack);
				return false;
			}
			int b = token.op != 'u' ? stack[--stack_size] : 0;
			int a = stack[--stack_size];

			switch (token.op)
			{
			case '+':
				stack[stack_size++] = a + b;
				break;
			case '-':
				stack[stack_size++] = a - b;
				break;
			case '*':
				stack[stack_size++] = a * b;
				break;
			case '/':
				if (b == 0)
				{
					free(stack);
					return false;
				}
				stack[stack_size++] = a / b;
				break;
			case '%':
				if (b == 0)
				{
					free(stack);
					return false;
				}
				stack[stack_size++] = a % b;
				break;
			case '^':
				stack[stack_size++] = (int)pow(a, b);
				break;	  // ✅ Используем `pow()`
			case 'u':
				stack[stack_size++] = -a;
			break;	  // ✅ Используем `pow()`
			default:
				free(stack);
				return false;
			}
		}
	}

	if (stack_size != 1)
	{
		free(stack);
		return false;
	}

	*result = stack[0];
	free(stack);
	return true;
}
