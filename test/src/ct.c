#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/ct.h"

void run(struct phrases phrases_) {
	FILE *fp = popen("../build/./cc ../input/main_t.c -t", "r");
	char output[PATH_MAX];
	int status;
	
	if (fp == NULL) error_t("error while opening ./cc");
	
	// assumes that the output had no errors (for now...)
	while (fgets(output, PATH_MAX, fp) != NULL) if (output[strlen(output) - 1] == '\n') break;
	 
	if ((status = pclose(fp)) == -1) error_t("the program failed with status -1");
	
	output[strlen(output)-1] = '\0';
	
	printf("input: %s\nexp: %s\noutput: %s\nexit: ", phrases_.input, phrases_.exp, output);
	
	if (assert(phrases_.exp, output)) printf("OK\n");
	else printf("not match\n");
	
	printf("the program exit with status: %d\n", status);
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
