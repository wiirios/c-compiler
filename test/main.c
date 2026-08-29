#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/token.h"
#include "include/utils.h"
#include "include/reader.h"
#include "include/hashtable.h"
#include "include/lexer.h"
#include "include/parser.h"

#define DEBUG 1

/*
 *
 *	
*/
static int block = 0;
static int phrase_type = -1;
static int assignment = 0;

int *ptr_phrase_type = &phrase_type;

int main(int argc, char *argv[]) {	
	if (argc < 2) error_t("argv < 2");
	
	FILE *file = get_file_t(argv[1]);
	
	char BUFFER_[BUFFER_SIZE_T];
	ht_t *ht = ht_init();
	
	tokens_t *tokens = init_tokens_t();
	
	while (feof(file) == 0) {	
		reader_file_t(BUFFER_, sizeof(BUFFER_), file, &block);
		scan_t(BUFFER_, &block, tokens);
		
		if (IS_SEMICOLON(BUFFER_[strlen(BUFFER_) - 1])) {
			if (get_grammar(tokens)) printf("valid grammar\n");
			else printf("invalid grammar\n");
		}
		
		memset(BUFFER_, 0, strlen(BUFFER_));
	}
	
	print_token_t_parser(tokens);
	free_tokens_t(tokens);
	free(tokens);
	ht_destroy(ht);
	fclose(file);
	
	#if TEST
	printf("\nnumber os blocks: %d", block);
	printf("\ntotal tokens read: %d\n", tokens->length);
	
	free(tokens);
	#else
	printf("\n");
	#endif	

	return 0;
}
