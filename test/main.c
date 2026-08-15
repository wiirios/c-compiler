#include <stdio.h>

#include "include/utils.h"
/*
 *
 *
*/

int main(int argc, char *argv[]) {
	if (argc < 2) error_t("argv < 2");
	
	FILE *file = fopen(argv[1], "r");
	
	if (!file) error_t("error while open argc 1");
	
	if (strcmp(strrchr(argv[1], '.'), ".c") != 0) error_t("Invalid file extension");
	
	char BUFFER_[BUFFER_SIZE_T];
	static int block = 0;
	
	while (feof(file) == 0) {
		
		reader_file_t(BUFFER_, sizeof(BUFFER_), file, &block);	
		scan_t(BUFFER_, &block);
		
		BUFFER_[0] = '\0';
	}
	
	printf("\nnumber os blocks: %d\n", block);
	
	fclose(file);
	return 0;
}
