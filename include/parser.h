#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>	// Добавляем для использования bool

typedef struct
{
	char type;	  // 'n' - число, 'o' - оператор
	int value;
	char op;
} Token;

typedef struct
{
	Token *tokens;
	int size;
} TokenList;

bool tokenize(const char *expr, TokenList *tokens);

#endif
