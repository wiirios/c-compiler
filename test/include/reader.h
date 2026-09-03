#ifndef READER_HEADER
#define READER_HEADER

#include <stdint.h>

#define IS_OPERATOR(c) (c == '+' || c == '-' || c == '/' || c == '*')
#define IS_PUNCTUATORS(c) (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')
#define IS_ASSIGNMENT(c) (c == '=')
#define IS_LOGICAL(c) (c == '&' || c == '|')
#define IS_RESERVED_WORD(c) (strcmp((c), "int") == 0 || strcmp((c), "char") == 0 || strcmp((c), "float") == 0 || strcmp((c), "long") == 0)
#define IS_SEMICOLON(c) (c == ';')

void reader_file_t(char *BUFFER_, size_t sizebuffer, FILE *file, int *block); 

FILE *get_file_t(const char *file_name);

int get_file_size_t(const char *file_name, size_t *out_size);

unsigned int get_file_line(void);

#endif
