#ifndef SEMA_H
#define SEMA_H

#include <stdio.h>

#include "parser.h"
#include "token.h"

void sema(ll_t *ll);

enum TYPE get_type(token_t *token);

int check_type(enum TYPE type_head, ll_t *ll);

#endif
