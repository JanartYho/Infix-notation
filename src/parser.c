#include <ctype.h>
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool tokenize(const char *expr, TokenList *tokens) {
    tokens->tokens = malloc(strlen(expr) * sizeof(Token));
    tokens->size = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) continue;

        Token token;
        if (isdigit(expr[i])) {
            token.type = 'n';
            token.value = atoi(&expr[i]);
            while (isdigit(expr[i + 1])) i++; 
        } else if (expr[i] == '*' && expr[i + 1] == '*') {
            token.type = 'o'; token.op = '^'; i++;  
        } else if (expr[i] == '>' && expr[i + 1] == '>') {
            token.type = 'o'; token.op = 'R'; i++;  
        } else if (expr[i] == '<' && expr[i + 1] == '<') {
            token.type = 'o'; token.op = 'L'; i++;  
        } else if (strchr("+-*/%^&|()", expr[i])) {
            token.type = 'o'; token.op = expr[i];
        } else if (expr[i] == '~') {
            token.type = 'u'; token.op = '~'; // Обозначаем унарный оператор
        } else {
            printf("Error: Invalid character '%c'\n", expr[i]);
            free(tokens->tokens);
            return false;
        }

        tokens->tokens[tokens->size++] = token;
    }

    return true;
}
