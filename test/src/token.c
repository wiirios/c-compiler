#include "../include/token.h"

typedef struct token {
	char *identifier;
	void *value;
	int block;
	enum TYPE type;
} token_t;

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
			token->value = malloc(sizeof(int));
			
			if (!token->value) error_t("error while allocating for token (int)");
			
			*(int*)token->value = *(int*)value;
			break;
		case 1:
			token->value = (char*) malloc(strlen(value) + 1);
			
			if (!token->value) error_t("error while allocating for token (char)");
			
			memcpy(token->value, value, strlen(value) + 1);
			
			break;
		case 4:
			token->value = malloc(sizeof(int));
			if (!token->value) error_t("error while allocating for token (int)");
			
			*(int*)token->value = *(int*)value;
			
			break;
		default:
			break;
	}
	
	token->block = *block;
	token->type = type;
	
	return token;
}

void print_token_t(token_t *token) {
	switch (token->type) {
		// int
        case 0:
            printf("<%s, %d>", token->identifier, *(int*)token->value);
            break;
        // char
        case 1:
			printf("<%s, %s>", token->identifier, (char*)token->value);
            break;
        // operator
        // punctuators
        // assigment
        case 4:
        case 5:
        case 6:
			printf("<%c>", *(char*)token->value);
            break;
        default:
			break;
	}
	
	#if SHOW_TYPE_TOKEN
		printf("%d", token->type);
	#endif
}

void free_token_t(token_t *token) {
	if (!token) error_t("alloc a token first");
	
	free(token);	
}
