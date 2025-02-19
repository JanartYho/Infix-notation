#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int precedence(char op) {
    if (op == '~' || op == '-') return 5; // Унарные операторы (наивысший приоритет)
    if (op == '&') return 4;
    if (op == '|') return 3;
    if (op == 'L' || op == 'R') return 2;
    return 0;
}

bool convert_to_rpn(TokenList *infix, TokenList *rpn) {
    Token *stack = malloc(infix->size * sizeof(Token));
    int stack_size = 0;

    printf("Converting to RPN...\n");

    for (int i = 0; i < infix->size; i++) {
        Token token = infix->tokens[i];

        // Обрабатываем унарные операторы и применяем их к следующему числу сразу
        if ((token.op == '-' || token.op == '~') &&
            (i == 0 || infix->tokens[i - 1].type == 'o' || infix->tokens[i - 1].op == '(')) {
            token.type = 'u';  // Помечаем как унарный оператор
            printf("Detected unary %c\n", token.op);

            // Применяем унарный оператор к следующему числу
            if (i + 1 < infix->size && infix->tokens[i + 1].type == 'n') {
                if (token.op == '-') {
                    infix->tokens[i + 1].value = -infix->tokens[i + 1].value;
                    printf("Applying unary -: %d\n", infix->tokens[i + 1].value);
                } else if (token.op == '~') {
                    infix->tokens[i + 1].value = ~infix->tokens[i + 1].value;
                    printf("Applying unary ~: %d\n", infix->tokens[i + 1].value);
                }
                continue; // Пропускаем запись унарного оператора в стек
            }
        }

        if (token.type == 'n') {
            printf("Adding number: %d\n", token.value);
            rpn->tokens[rpn->size++] = token;
        } else if (token.type == 'o') {
            while (stack_size > 0 && precedence(stack[stack_size - 1].op) >= precedence(token.op)) {
                rpn->tokens[rpn->size++] = stack[--stack_size];
            }
            stack[stack_size++] = token;
        } else if (token.op == ')') {
            while (stack_size > 0 && stack[stack_size - 1].op != '(') {
                rpn->tokens[rpn->size++] = stack[--stack_size];
            }
            stack_size--; // Убираем '('
        }
    }

    while (stack_size > 0) {
        rpn->tokens[rpn->size++] = stack[--stack_size];
    }

    free(stack);
    printf("RPN conversion done\n");
    return true;
}
