#ifndef TOKEN_HEADER
#define TOKEN_HEADER

#include "utils.h"

#define SHOW_TYPE_TOKEN 0

enum TYPE {
	INTEGER_ENUM,
	CHAR_ENUM,
	FLOAT_ENUM,
	LONG_ENUM,
	OPERATOR_ENUM,
	PUNCTUATORS_ENUM,
	ASSIGMENT_ENUM
};

typedef struct token token_t;

token_t *init_token_t(char *identifier, void *value, int *block, enum TYPE type);

void print_token_t(token_t *token);
void free_token_t(token_t *token);

#endif
