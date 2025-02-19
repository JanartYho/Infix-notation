#include "evaluate.h"
#include <stdlib.h>
#include <stdio.h>

bool evaluate_rpn(TokenList *rpn, int *result) {
    int *stack = malloc(rpn->size * sizeof(int));
    int stack_size = 0;

    for (int i = 0; i < rpn->size; i++) {
        Token token = rpn->tokens[i];

        if (token.type == 'n') {
            printf("PUSH %d\n", token.value);
            stack[stack_size++] = token.value;
        } else if (token.type == 'o') { // Бинарные операторы
            if (stack_size < 2) {
                printf("Error: Stack underflow on binary operator '%c'\n", token.op);
                free(stack);
                return false;
            }
            int b = stack[--stack_size];
            int a = stack[--stack_size];

            switch (token.op) {
                case '+': stack[stack_size++] = a + b; printf("%d + %d = %d\n", a, b, a + b); break;
                case '-': stack[stack_size++] = a - b; printf("%d - %d = %d\n", a, b, a - b); break;
                case '*': stack[stack_size++] = a * b; printf("%d * %d = %d\n", a, b, a * b); break;
                case '/': stack[stack_size++] = a / b; printf("%d / %d = %d\n", a, b, a / b); break;
                case '%': stack[stack_size++] = a % b; printf("%d %% %d = %d\n", a, b, a % b); break;
                case '^': stack[stack_size++] = a ^ b; printf("%d ^ %d = %d\n", a, b, a ^ b); break;
                case '&': stack[stack_size++] = a & b; printf("%d & %d = %d\n", a, b, a & b); break;
                case '|': stack[stack_size++] = a | b; printf("%d | %d = %d\n", a, b, a | b); break;
                case 'L': stack[stack_size++] = a << b; printf("%d << %d = %d\n", a, b, a << b); break;
                case 'R': stack[stack_size++] = a >> b; printf("%d >> %d = %d\n", a, b, a >> b); break;
                default:
                    printf("Error: Unknown operator '%c'\n", token.op);
                    free(stack);
                    return false;
            }
        }
    }

    if (stack_size != 1) {
        printf("Error: Stack did not collapse to single result, stack_size = %d\n", stack_size);
        free(stack);
        return false;
    }

    *result = stack[0];
    printf("Final result: %d\n", *result);
    free(stack);
    return true;
}
