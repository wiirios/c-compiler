#ifndef SEMA_H
#define SEMA_H

#include <stdio.h>

#include "parser.h"
#include "token.h"

enum TYPE get_type(token_t *token);

int sema(ll_t *ll);
int check_type(enum TYPE type_head, ll_t *ll);

#endif
