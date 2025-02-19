#include "error_handling.h"
#include "evaluate.h"
#include "parser.h"
#include "shunting_yard.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"expression\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *expression = argv[1];

    printf("Input expression: %s\n", expression); // Отладочный вывод

    TokenList tokens;
    if (!tokenize(expression, &tokens)) {
        print_error(INVALID_EXPRESSION);
        return INVALID_EXPRESSION;
    }

    printf("Tokenization successful\n"); // Отладочный вывод

    TokenList rpn;
    rpn.tokens = malloc(tokens.size * sizeof(Token)); // Инициализация памяти для RPN
    rpn.size = 0;

    if (!convert_to_rpn(&tokens, &rpn)) {
        print_error(SYNTAX_ERROR);
        return SYNTAX_ERROR;
    }

    printf("RPN conversion successful\n"); // Отладочный вывод

    int result;
    if (!evaluate_rpn(&rpn, &result)) {
        print_error(EVALUATION_ERROR);
        return EVALUATION_ERROR;
    }

    printf("Evaluation successful\n"); // Отладочный вывод
    printf("Result: %d\n", result); // Вывод результата

    free(tokens.tokens);
    free(rpn.tokens);
    return EXIT_SUCCESS;
}
