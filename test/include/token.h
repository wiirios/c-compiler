#ifndef TOKEN_HEADER
#define TOKEN_HEADER

#include "utils.h"

#define SHOW_TYPE_TOKEN 0

enum TYPE {
	INTEGER_ENUM,			// 0
	CHAR_ENUM,				// 1
	FLOAT_ENUM,				// 2
	LONG_ENUM,				// 3
	OPERATOR_ENUM,			// 4
	PUNCTUATORS_ENUM,		// 5
	ASSIGMENT_ENUM,			// 6
	LOGICAL_ENUM,			// 7
	RESERVED_ENUM			// 8
};

enum TOKEN_RESERVED_KEYWORD {
	IF_TOKEN,
	ELSE_TOKEN,
	FOR_TOKEN,
	WHILE_TOKEN,
};

typedef struct token token_t;

token_t *init_token_t(char *identifier, void *value, int *block, enum TYPE type);

void print_token_t(token_t *token);
void free_token_t(token_t *token);

#endif
