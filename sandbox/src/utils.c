#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/utils.h"
#include "../include/dock.h"

extern dock_t *dock;
extern unsigned int line;

int error(const char *msg) {
	fprintf(stderr, "%s\n", msg);
	
	destroy_dock(dock);
	
	exit(EXIT_FAILURE);
}

void panic_mode(tokens_t *tokens) {
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
			
			l += print_token(tokens->array_tokens[j], 0);
			l += print_token(tokens->array_tokens[i], 0);
			
			printf("\n");
			for (; k < l; k++) putchar('~');
		}
	}
	
	printf("\n");
}

unsigned int get_file_line() {
	return line;
}
