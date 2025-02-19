#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "parser.h"

bool convert_to_rpn(TokenList *infix, TokenList *rpn);

#endif
