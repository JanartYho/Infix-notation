#include <ctype.h>	  // Для функций работы с символами
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>	   // Для malloc и free
#include <string.h>	   // ✅ Добавляем этот заголовок, чтобы использовать strlen() и strchr()

bool tokenize(const char *expr, TokenList *tokens)
{
	tokens->tokens = malloc(strlen(expr) * sizeof(Token));
	tokens->size = 0;

	for (int i = 0; expr[i] != '\0'; i++)
	{
		if (isspace(expr[i]))
			continue;	 // Пропускаем пробелы

		if (isdigit(expr[i]))
		{
			tokens->tokens[tokens->size].type = 'n';
			tokens->tokens[tokens->size].value = atoi(&expr[i]);
			tokens->size++;
			while (isdigit(expr[i + 1]))
				i++;
		}
		else if (expr[i] == '*' && expr[i + 1] == '*')
		{
			tokens->tokens[tokens->size].type = 'o';
			tokens->tokens[tokens->size].op = '^';	  // ✅ `**` заменяем на `^`
			tokens->size++;
			i++;	// Пропускаем второй `*`
		}
		/*else if (expr[i] == '>' && expr[i + 1] == '>')
		{
			tokens->tokens[tokens->size].type = 'o';
			tokens->tokens[tokens->size].op = 'L';	  // ✅ `**` заменяем на `^`
			tokens->size++;
			i++;	// Пропускаем второй `*`
		}
		else if (expr[i] == '<' && expr[i + 1] == '<')
		{
			tokens->tokens[tokens->size].type = 'o';
			tokens->tokens[tokens->size].op = 'L';	  // ✅ `**` заменяем на `^`
			tokens->size++;
			i++;	// Пропускаем второй `*`
		}*/
		else if (strchr("+-", expr[i]) && isdigit(expr[i + 1]))
		{
			if (expr[i] == '-')
			{
				tokens->tokens[tokens->size].type = 'o';
				tokens->tokens[tokens->size].op = 'u';
			}

			tokens->size++;
		}
		else if (strchr("+-*/%^()", expr[i]))
		{
			tokens->tokens[tokens->size].type = 'o';
			tokens->tokens[tokens->size].op = expr[i];
			tokens->size++;
		}
		else
		{
			return false;	 // Ошибка: неизвестный символ
		}
	}

	return true;
}
