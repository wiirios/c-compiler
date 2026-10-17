#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "include/utils.h"
#include "include/ct.h"

#define FLAGS_ON 1

int main(int argc, char *argv[]) {
	FILE *fp = popen(DEFAULT_PATH, "r");
	char output[PATH_MAX];
	int status;
	
	if (fp == NULL) error_t("error while opening ./cc");	
		
	while (fgets(output, PATH_MAX, fp) != NULL) printf("%s", output);
	
	if ((status = pclose(fp)) == -1) error_t("the program failed with status -1");
	
	printf("the program exit with status: %d\n", status);

	return 0;
}
