#include <stdio.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/ct.h"

int run(void) {
	return 0;	
}

int read_exp(char *file_name, char *input, char *exp) {
	FILE *file = fopen(file_name, "r");
	
	if (!file) error_t("error while open exp");
	int c, i, exp_;
	i = exp_ = 0;
	
	while ((c = fgetc(file)) != EOF) {
		if (c == '#') {
			while ((c = fgetc(file)) != EOF && c != '\n') continue;
			
			continue;
		}
		
		if (c != '\n' && !exp_) {
			input[i] = c;
			i++;
		}
		
		if (i && c == '\n') {
			exp_ = 1;
			i = 0;
		}
		
		if (c != '\n' && exp_ ) {
			exp[i] = c;
			i++;	
		}
	}
	
	input[strlen(input)] = '\0';
	exp[strlen(exp)] = '\0';
	
	return 1;
}

int assert(char *exp, char *output) {
	if (strcmp(exp, output) == 0) return 1;
	
	return 0;
}
