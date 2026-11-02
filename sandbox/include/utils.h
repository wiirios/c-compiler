#ifndef UTILS_HEADER
#define UTILS_HEADER

#include "token.h"

#define BUFFER_SIZE_T 1024

unsigned int get_file_line();

int error(const char *msg);

void panic_mode(tokens_t *tokens);

#endif
