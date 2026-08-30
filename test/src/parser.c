#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/parser.h"
#include "../include/utils.h"

// todo: implement operator precedence (and apply this to the linked list responsible for assembling the sequence of tokens)

int parser(tokens_t *tokens) {
	if (tokens->length < 5) return 0;
	
	ll_t *ll = init_ll();
	
	if (!declaration(ll, tokens)) {
		free_ll(ll);
		free_tokens_t(tokens);
		error_t("invalid declaration");	
	}
	print_ll(ll);
	free_ll(ll);
	return 1;
} 

void print_token_t_parser(tokens_t *tokens) {
	for (int i = 0; i < tokens->length; i++) if (tokens->array_tokens[i] != NULL) printf("token->identifier: %s at :[%d]\n", tokens->array_tokens[i]->identifier, i);
}

int declaration(ll_t *ll, tokens_t *tokens) {
	int (*alldecl[DECLARATION_SIZE])(token_t *token) = 
	{	type, 
		id, 
		assigment, 
		expression, 
		semicolon
	};
	int i, j, i_c;
	i = j = i_c = 0;
	
	while (tokens->array_tokens[j] != NULL) {
		if (i_c >= 1) {
			while (1) {
				if (tokens->array_tokens[j]->type == OPERATOR_ENUM && tokens->array_tokens[j + 1]->type == INTEGER_ENUM) goto binary;
				
				if (tokens->array_tokens[j]->type == INTEGER_ENUM && tokens->array_tokens[j - 1]->type == INTEGER_ENUM) return 0;
				
				if (tokens->array_tokens[j]->type == SEMICOLON_ENUM) break;
				
				if(!alldecl[i - 1](tokens->array_tokens[j])) return 0;
				
				binary:
				insert_node(ll, tokens->array_tokens[j]);
				j++;
			}

			i_c = 0;
		}
		
		if (!alldecl[i](tokens->array_tokens[j])) return 0;
		
		insert_node(ll, tokens->array_tokens[j]);
		
		if (tokens->array_tokens[j]->type == INTEGER_ENUM) i_c++;
				
		i++;
		j++;
	}
	
	return 1;
}

int type(token_t *token) {
	if (token->type != RESERVED_ENUM) return 0;
	
	return 1;
}

int id(token_t *token) {
	if (token->identifier == NULL || *token->identifier == '\0') return 0;
	
	return 1;
}

int assigment(token_t *token) {
	if (token->type != ASSIGMENT_ENUM && !IS_ASSIGNMENT(*token->identifier) && strlen(token->identifier) != 1) return 0;
	
	return 1;
}

int expression(token_t *token) {
	if (!factor(token)) return 0;
	
	return 1;
}

int factor(token_t *token) {
	if (!number(token)) return 0;
	
	return 1;
}

int number(token_t *token) {
	if (token->type != INTEGER_ENUM) return 0;
	
	return 1;
}

int semicolon(token_t *token) {
	if (token->type != SEMICOLON_ENUM && !IS_SEMICOLON(*token->identifier) && strlen(token->identifier) != 1) return 0;
	
	return 1;
}

ll_t *init_ll(void) {
	ll_t *ll = (ll_t*) malloc(sizeof(ll_t));

	if (!ll) {
		//
		error_t("Error while creating linked list\n");
	}
	
	ll->head = NULL;
	
	return ll;
}

node_t *init_node(token_t *token) {
	node_t *node = (node_t*) malloc(sizeof(node_t));
	
	if (!node) {
		error_t("\n");	
	}
	
	node->next = NULL;
	node->token = token;
	
	return node;
}

void insert_node(ll_t *ll, token_t *token) {
	node_t *node = init_node(token);
	
	if (ll->head == NULL) {
		ll->head = node;
		
		return;
	}
	
	for (node_t *current = ll->head; current != NULL; current = current->next) {
		if (current->next == NULL) {
			current->next = node;
			break;
		}
	}	
}

void free_ll(ll_t *ll) {
	node_t *current;
	
	while ((current = ll->head) != NULL) {
		ll->head = ll->head->next;
		free(current);	
	}
}

void print_ll(ll_t *ll) {
	node_t *current;
	
	while ((current = ll->head) != NULL) {
		printf("ll token->identifier: %s\n", current->token->identifier);	
		ll->head = ll->head->next;
	}
}
