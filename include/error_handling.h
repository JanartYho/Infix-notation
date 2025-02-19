#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>
#include <stdlib.h>

// Коды ошибок
#define INVALID_EXPRESSION 1
#define SYNTAX_ERROR 2
#define EVALUATION_ERROR 3

// Функция вывода ошибок
void print_error(int error_code);

#endif
