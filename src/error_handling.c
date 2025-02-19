#include "error_handling.h"

void print_error(int error_code)
{
	switch (error_code)
	{
	case INVALID_EXPRESSION:
		fprintf(stderr, "Error: Invalid expression\n");
		break;
	case SYNTAX_ERROR:
		fprintf(stderr, "Error: Syntax error in expression\n");
		break;
	case EVALUATION_ERROR:
		fprintf(stderr, "Error: Evaluation error (e.g., division by zero)\n");
		break;
	default:
		fprintf(stderr, "Error: Unknown error occurred\n");
		break;
	}
}
