#include "shunting_yard.h"

#include <stdio.h>
#include <stdlib.h>

// ✅ Функция `precedence()` вынесена ВНЕ `convert_to_rpn()`
int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/' || op == '%')
		return 2;
	if (op == '^')
		return 3;	 // `^` самый высокий приоритет
	return 0;
}

bool convert_to_rpn(TokenList *infix, TokenList *rpn)
{
	printf("Converting to RPN...\n");

	rpn->tokens = malloc(infix->size * sizeof(Token));
	rpn->size = 0;

	Token *stack = malloc(infix->size * sizeof(Token));
	if (!stack)
		return false;

	int stack_size = 0;

	for (int i = 0; i < infix->size; i++)
	{
		Token token = infix->tokens[i];

		printf("Processing token: ");
		if (token.type == 'n')
			printf("Number %d\n", token.value);
		else
			printf("Operator %c\n", token.op);

		if (token.type == 'n')
		{
			rpn->tokens[rpn->size++] = token;
		}
		else if (token.op == '(')
		{
			stack[stack_size++] = token;
		}
		else if (token.op == ')')
		{
			while (stack_size > 0 && stack[stack_size - 1].op != '(')
			{
				rpn->tokens[rpn->size++] = stack[--stack_size];
			}
			if (stack_size == 0)
			{
				printf("Error: Unmatched ')'\n");
				free(stack);
				return false;
			}
			stack_size--;	 // Удаляем `(`
		}
		else
		{
			// ✅ Исправлено: `^` работает справа-налево!
			while (stack_size > 0 && stack[stack_size - 1].op != '(' &&
				   ((token.op != '^' && precedence(stack[stack_size - 1].op) >= precedence(token.op)) ||
					(token.op == '^' && precedence(stack[stack_size - 1].op) > precedence(token.op))))
			{
				rpn->tokens[rpn->size++] = stack[--stack_size];
			}
			stack[stack_size++] = token;
		}
	}

	while (stack_size > 0)
	{
		if (stack[stack_size - 1].op == '(')
		{
			printf("Error: Unmatched '('\n");
			free(stack);
			return false;
		}
		rpn->tokens[rpn->size++] = stack[--stack_size];
	}

	free(stack);
	return true;
}
