#include "error_handling.h"
#include "evaluate.h"
#include "parser.h"
#include "shunting_yard.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s \"expression\"\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *expression = argv[1];

	TokenList tokens;
	if (!tokenize(expression, &tokens))
	{
		print_error(INVALID_EXPRESSION);
		return INVALID_EXPRESSION;
	}

	TokenList rpn;
	if (!convert_to_rpn(&tokens, &rpn))
	{
		print_error(SYNTAX_ERROR);
		return SYNTAX_ERROR;
	}

	int result;
	if (!evaluate_rpn(&rpn, &result))
	{
		print_error(EVALUATION_ERROR);
		return EVALUATION_ERROR;
	}

	printf("%d\n", result);
	return EXIT_SUCCESS;
}
