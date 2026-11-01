#include <string.h>

#include "../include/sema.h"
#include "../include/utils.h"

void sema(ll_t *ll) {	
	enum TYPE type_ = get_type(ll->head->token);
	
}

enum TYPE get_type(token_t *token) {
	if (token->type > TYPES_LENGTH) error_t("type not recognized");
	
	enum TYPE type;
	
	if (strcmp(token->identifier, "INT") == 0) type = 0;
	else if (strcmp(token->identifier, "CHAR") == 0) type = 1;
	else if (strcmp(token->identifier, "FLOAT") == 0) type = 2;
	else if (strcmp(token->identifier, "LONG") == 0) type = 3;
	
	return type;
}

int check_type(enum TYPE type_head, ll_t *ll) {
	node_t *current;
	int i = 0;
	
	// skip type, id, assigment
	while (i < 3) {
		ll->head = ll->head->next;
		i++;
	}
	
	while ((current = ll->head) != NULL) {
		if (current->token->type == SEMICOLON_ENUM) break;
		
		if (current->token->type == OPERATOR_ENUM || current->token->type == type_head) {
			ll->head = ll->head->next;
			continue;	
		}
		else return 0;
	}
	
	return 1;
}
