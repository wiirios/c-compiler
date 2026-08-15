#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "reader.h"
#include "lexer.h"
#include "token.h"

#define BUFFER_SIZE_T 1024

int error_t(const char *msg);

#endif
