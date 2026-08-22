#include <stdio.h>

#include "include/utils.h"

#define TEST 1

/*
 *
 *
*/
static int block = 0;
static int phrase_type = -1;
int *ptr_phrase_type = &phrase_type;

int main(int argc, char *argv[]) {
	#if TEST
	
	ht_t *ht = ht_init();
	
	ht_printall(ht);
	
	get(ht, "float");
	get(ht, "char");
	
	hte_destroy(ht);
	ht_destroy(ht);
	
	printf("exiting...\n");	
	exit(EXIT_SUCCESS);
	#endif
	
	
	if (argc < 2) error_t("argv < 2");
	
	FILE *file = get_file_t(argv[1]);
	
	char BUFFER_[BUFFER_SIZE_T];
	
	while (feof(file) == 0) {	
		reader_file_t(BUFFER_, sizeof(BUFFER_), file, &block);	
		scan_t(BUFFER_, &block);
		
		memset(BUFFER_, 0, strlen(BUFFER_));
	}
	
	printf("\nnumber os blocks: %d\n", block);
	
	fclose(file);
	return 0;
}
