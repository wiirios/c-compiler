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
	
	if (argc > 1) {
		if (strcmp(argv[1], "-i") == 0) {
			FILE *inputf = fopen("../input/main_t.c", "w");
		
			if (!inputf) error_t("error while opening ../input/main_t.c");
		
			fprintf(inputf, "%s%s", &input[0], "\n");
		
			fclose(inputf);
		}
	}
	
	struct phrases phrases_;
	strcpy(phrases_.input, input);
	strcpy(phrases_.exp, exp);
	
	run(phrases_);
	
	return 0;
}
