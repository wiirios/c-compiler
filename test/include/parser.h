#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "reader.h"

#define DECLARATION_SIZE 5

void print_token_t_parser(tokens_t *tokens);

int parser(tokens_t *tokens);

int type(token_t *token);
int id(token_t *token);
int assigment(token_t *token);
int expression(token_t *token);
int semicolon(token_t *token);

typedef struct node node_t;
typedef struct ll ll_t;

struct ll {
	node_t *head;
};

struct node {
	token_t *token;
	node_t *next;
};

ll_t *init_ll(void);
node_t *init_node(token_t *token);

int declaration(ll_t *ll, tokens_t *tokens);

void insert_node(ll_t *ll, token_t *token);
void free_ll(ll_t *ll);
void print_ll(ll_t *ll);

#endif

/*
 * declaration -> type id = expression ;
 * type -> int | char | float | long
 * id -> [Aa-Zz]+
*/

/*
 * expression -> factor
 * expression -> factor + factor
 * 				| factor - factor
 * 				| factor / factor
 * 				| factor * factor
 * 				| (expression)
 * 				| expression 
 * factor -> number+
 * number -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
 */

