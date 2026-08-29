#ifndef LEXER_HEADER
#define LEXER_HEADER

#include "token.h"

enum PRIMITIVE_DATA_TYPE_C_ENUM {
	INTEGER_PRIMITIVE_DATA_TYPE,
	CHAR_PRIMITIVE_DATA_TYPE,
	FLOAT_PRIMITIVE_DATA_TYPE,
	LONG_PRIMITIVE_DATA_TYPE
};

void scan_t(char *phrase, int *block, tokens_t *tokens);

int get_phrase_type(char *buffer);

#endif
