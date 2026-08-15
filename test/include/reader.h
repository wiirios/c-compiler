#ifndef READER_HEADER
#define READER_HEADER

#include "utils.h"

#define IS_OPERATOR(c) (c == '+' || c == '-' || c == '/' || c == '*')
#define IS_PUNCTUATORS(c) (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')
#define IS_ASSIGNMENT(c) (c == '=')

/*
 * 
 * 
 * file
 * |----- reader
 * 			|------ scan
 *
 * o reader vai ler ate encontrar um ' '
 * int bn = 10;
 *  
 */
void reader_file_t(char *BUFFER_, size_t sizebuffer, FILE *file, int *block); 

#endif
