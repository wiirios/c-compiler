#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "include/utils.h"
#include "include/ct.h"

int main(int argc, char *argv[]) {
	char input[64];
	char exp[64];
	
	read_exp("exp", input, exp);
	
	// implement an option capable of running the ./cc given the input in the exp file
	/**
	 * char input;
	 * read_exp("exp", input, exp);
	 * ./cc ../input/main_t.c -t -i input
	 */
	FILE *fp = popen("../build/./cc ../input/main_t.c -t", "r");
	char output[PATH_MAX];
	int status;
	
	if (fp == NULL) error_t("error while opening ./cc");
	
	// assumes that the output had no errors (for now...)
	while (fgets(output, PATH_MAX, fp) != NULL) if (output[strlen(output) - 1] == '\n') break;
	 
	if ((status = pclose(fp)) == -1) error_t("the program failed with status -1");
	
	output[strlen(output)-1] = '\0';
	
	printf("input: %s\n", input);
	printf("exp: %s\n", exp);
	printf("output: %s\n", output);
	printf("exit: ");
	if (assert(exp, output)) printf("OK\n");
	else printf("not match\n");
	
	printf("the program exit with status: %d\n", status);

	return 0;
}
