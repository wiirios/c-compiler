#include "../include/token.h"

typedef struct token {
	char *identifier;
	int value;
	int block;
	enum TYPE type;
} token_t;

token_t *init_token_t(char *identifier, int value, int *block, enum TYPE type) {
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
	token->type = type;
	
	return token;
}

void print_token_t(token_t *token) {	
	switch (token->type) {
		// int
        case 0:
            printf("<%s, %d>", token->identifier, token->value);
            break;
        // operator
        case 1:
            printf("<%c>", token->value);
            break;
        default:
			break;	
	}
}

void free_token_t(token_t *token) {
	if (!token) error_t("alloc a token first");
	
	free(token);	
}

