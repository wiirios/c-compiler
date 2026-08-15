#ifndef TOKEN_HEADER
#define TOKEN_HEADER

#include "utils.h"

typedef struct token token_t;

token_t *init_token_t(char *identifier, int value, int *block);

void print_token_t(token_t *token);
void free_token_t(token_t *token);

#endif
