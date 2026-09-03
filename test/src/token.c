#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/token.h"
#include "../include/utils.h"

token_t *init_token_t(char *identifier, void *value, int *block, enum TYPE type) {
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
	
	switch (type) {
		case 0:
		case 4:
		case 5:
		case 6:
		case 9:
			token->value = malloc(sizeof(int));
			
			if (!token->value) error_t("error while allocating for token (int)");
			*(int*)token->value = *(int*)value;
			break;
		case 1:
		case 8:
			token->value = (char*) malloc(strlen(value) + 1);
			
			if (!token->value) error_t("error while allocating for token (char)");
			
			memcpy(token->value, value, strlen(value) + 1);			
			break;
		default:
			break;
	}
	
	token->block = *block;
	token->type = type;
	token->panic_s.error = '\0';
	token->panic_s.error = -1;
	
	return token;
}

tokens_t *init_tokens_t() {
	tokens_t *tokens;
	tokens = (tokens_t*) malloc(sizeof(tokens_t));
	
	if (!tokens) error_t("error while allocated token");
	
	tokens->length = 0;
	
	return tokens;
}

int print_token_t(token_t *token) {	
	int length = 0;
	
	switch (token->type) {
		// int
        case 0:
            length = printf("<%s, %d>", token->identifier, *(int*)token->value);
            break;
        // char
        case 1:
			length = printf("<%s, %s>", token->identifier, (char*)token->value);
            break;
        // operator
        // punctuators
        // assigment
        // logical
        // semicolon
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
			length = printf("<%c>", *(int*)token->value);
            break;
        // reserved
        case 8:
			length = printf("<%s>", (char*)token->identifier);
			break;
        default:
			error_t("type not found");
			break;
	}
	
	#if SHOW_TYPE_TOKEN
		printf("%d", token->type);
	#endif
	
	return length;
}

void free_token_t(token_t *token) {
	if (!token) error_t("alloc a token first");
	
	free(token);
}

void free_tokens_t(tokens_t *tokens) {
	for (int i = 0; i < tokens->length; i++) if (tokens->array_tokens[i] != NULL) free_token_t(tokens->array_tokens[i]);	
}
