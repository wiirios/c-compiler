#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/parser.h"
#include "../include/utils.h"

/*
 * declaration -> type id = expresion ;
 * type -> int | char | float | long
 * id -> [Aa-Zz]+
*/

/*
 * expression -> factor
 * expression -> factor + factor
 * 				| factor - factor
 * 				| factor / factor
 * 				| factor * factor
 * 				| (expression)
 * 				| expression 
 * factor -> number+
 * number -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
 */

void print_token_t_parser(tokens_t *tokens) {
	for (int i = 0; i < tokens->length; i++) if (tokens->array_tokens[i] != NULL) printf("token->identifier: %s at :[%d]\n", tokens->array_tokens[i]->identifier, i);
}

int declartion(tokens_t *tokens) {
	return 0;
}

int get_grammar(tokens_t *tokens) {
	return 1;
}
