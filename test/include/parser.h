#ifndef PARSER_H
#define PARSER_H

#include "token.h"

void print_token_t_parser(tokens_t *tokens);

int declartion(tokens_t *tokens);
int get_grammar(tokens_t *tokens);

#endif
