#include "../include/token.h"

typedef struct token {
	char *identifier;
	int value;
	int block;
} token_t;

token_t *init_token_t(char *identifier, int value, int *block) {
	if (!identifier) error_t("invalid token identifier");
	
	if (block < 0) error_t("a block cannot be negative");
	
	token_t *token;
	token = (token_t*) malloc(sizeof(token_t));
	
	if (!token) {
		free(token);
		error_t("error while allocated token");
	}
	
	token->identifier = (char*) malloc(strlen(identifier) + 1);
	
	if (!token->identifier) error_t("error while allocanting identifier");
	
	memcpy(token->identifier, identifier, strlen(identifier) + 1);
	
	token->value = value;
	token->block = *block;
	
	return token;
}

void print_token_t(token_t *token) {
	printf("<%s, %d>", token->identifier, token->value);
		
	
}

void free_token_t(token_t *token) {
	if (!token) error_t("alloc a token first");
	
	free(token);	
}

