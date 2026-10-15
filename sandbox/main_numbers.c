#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main () {		
	FILE *f = fopen("main_number.c", "r");
	
	if (!f) {
		fprintf(stderr, "%s: %s\ncode exit: %d\n", "test", strerror(errno), errno);
		exit(EXIT_FAILURE);	
	}	
	else fclose(f);
	
	return 0;
}
