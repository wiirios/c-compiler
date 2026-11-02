#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/parser.h"
#include "../include/utils.h"
#include "../include/dock.h"
#include "../include/hashtable.h"
#include "../include/sema.h"

extern int line;
extern dock_t *dock;
extern ht_t *ht;

const char *panic_msg[] = {
	"type error",
	"id error",
	"assigment error",
	"expression error",
	"factor error",
	"number error",
	"semicolon error",
	"previous definition",
	"incompatible type"
};

// todo: implement operator precedence (and apply this to the linked list responsible for assembling the sequence of tokens)

int parser(tokens_t *tokens) {
	if (tokens->length < 5) return 0;
	
	ll_t *ll = init_ll();
	insert_ship_t(dock, ll, TYPEITEM_LL);
	
	if (!declaration(ll, tokens)) {
		panic(tokens);
		error_t("invalid declaration.");
	}
	
	if (ht_get(ht, tokens->array_tokens[1]) == 1) {
		set_error(tokens->array_tokens[1], 7);
		panic(tokens);
		error_t("the variable has already been declared in the same block.");
	}
	
	ht_insert(ht, hte_create_entry(tokens->array_tokens[1]->value, tokens->array_tokens[1]->type, tokens->array_tokens[1]->block));
	if (!sema(ll)) {
		set_error(tokens->array_tokens[1], 8);
		panic(tokens);
		error_t("the value assigned to the variable is different from the one that was declared.");
	}
	
	free_ll(ll);
	return 1;
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
				
				if (tokens->array_tokens[j]->type == INTEGER_ENUM && tokens->array_tokens[j - 1]->type == INTEGER_ENUM) {
					
					return 0;
				}
				
				if (tokens->array_tokens[j]->type == SEMICOLON_ENUM) break;
				
				if (!alldecl[i - 1](tokens->array_tokens[j])) {
					
					return 0;
				}
				
				binary:
					insert_node(ll, tokens->array_tokens[j]);
					j++;
			}

			i_c = 0;
		}
		
		if (!alldecl[i](tokens->array_tokens[j])) {
			
			return 0;	
		}
		
		insert_node(ll, tokens->array_tokens[j]);
		
		if (tokens->array_tokens[j]->type == INTEGER_ENUM) i_c++;
				
		i++;
		j++;
	}
	
	return 1;
}

int type(token_t *token) {
	if (token->type != RESERVED_ENUM) {
		set_error(token, 0);
		return 0;	
	}
	
	return 1;
}

int id(token_t *token) {
	if (token->identifier == NULL || *token->identifier == '\0') {
		set_error(token, 1);
		return 0;
	}
	
	return 1;
}

int assigment(token_t *token) {
	if (token->type != ASSIGMENT_ENUM && !IS_ASSIGNMENT(*token->identifier) && strlen(token->identifier) != 1) {
		set_error(token, 2);
		return 0;
	}
	
	return 1;
}

int expression(token_t *token) {
	if (!factor(token)) {
		set_error(token, 3);
		return 0;
	}
	
	return 1;
}

int factor(token_t *token) {
	if (!number(token)) {
		set_error(token, 4);
		return 0;
	}
	
	return 1;
}

int number(token_t *token) {
	if (token->type != INTEGER_ENUM) {
		set_error(token, 5);
		return 0;
	}
	
	return 1;
}

int semicolon(token_t *token) {
	if (token->type != SEMICOLON_ENUM && !IS_SEMICOLON(*token->identifier) && strlen(token->identifier) != 1) {
		set_error(token, 6);
		return 0;
	}
	
	return 1;
}

ll_t *init_ll(void) {
	ll_t *ll = (ll_t*) malloc(sizeof(ll_t));

	if (!ll) error_t("Error while creating linked list\n");
		
	ll->head = NULL;
	
	return ll;
}

node_t *init_node(token_t *token) {
	node_t *node = (node_t*) malloc(sizeof(node_t));
	
	if (!node) error_t("\n");
	
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
	printf("\n");
	while ((current = ll->head) != NULL) {
		printf("ll token->identifier: %s\n", current->token->identifier);	
		ll->head = ll->head->next;
	}
}

void panic(tokens_t *tokens) {
	// i index used to walk through the token array
	// j index of the token immediately before the faulty one
	// k total width (in characters) of the printed tokens, i.e. how many '~' to print
	// l counter for the '~' characters already printed
	int i, j, k, l;
	i = j = k = l = 0;
	
	for (; i < tokens->length; i++) {
		if (tokens->array_tokens[i]->panic_s.error == 1) { 
			j = i - 1;
			
			printf("\nerror: line=%d", get_file_line());
			printf("\nexpected: [%s] at:\n", tokens->array_tokens[i]->panic_s.msg);
			
			l += print_token_t(tokens->array_tokens[j], 0);
			l += print_token_t(tokens->array_tokens[i], 0);
			
			printf("\n");
			for (; k < l; k++) putchar('~');
		}
	}
	
	printf("\n");
}

void set_error(token_t *token, int index) {
	token->panic_s.error = 1;
	memcpy(token->panic_s.msg, panic_msg[index], strlen(panic_msg[index]));
}
