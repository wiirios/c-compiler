#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/token.h"
#include "include/utils.h"
#include "include/reader.h"
#include "include/hashtable.h"
#include "include/lexer.h"
#include "include/parser.h"

static int block = 0;
static int phrase_type = -1;
static int assignment = 0;
ht_t *ht = NULL;

int *ptr_phrase_type = &phrase_type;

int main(int argc, char *argv[]) {	
	if (argc < 2) error_t("argv < 2");
	
	FILE *file = get_file_t(argv[1]);
	
	char BUFFER_[BUFFER_SIZE_T];
	ht = ht_init();
	
	tokens_t *tokens = init_tokens_t();
	
	while (feof(file) == 0) {	
		reader_file_t(BUFFER_, sizeof(BUFFER_), file, &block);
		scan_t(BUFFER_, &block, tokens);
		
		if (IS_SEMICOLON(BUFFER_[strlen(BUFFER_) - 1]) || IS_PUNCTUATORS(BUFFER_[strlen(BUFFER_) - 1])) {
			if (!parser(tokens)) printf("\ninvalid grammar\n");
			else printf("\nvalid grammar\n");
			
			if (argc == 3) {
				if (strcmp(argv[2], "-y") == 0) {
					printf("\n--\n");
					for (int i = 0; i < tokens->length; i++) {
						if (tokens->array_tokens[i]) {
							printf("array_tokens[%d] = ", i);
							print_token_t(tokens->array_tokens[i]);
							printf(" || type: %d" , tokens->array_tokens[i]->type);
							printf(" || block: %d", tokens->array_tokens[i]->block);
							printf("\n");
						}
					}
					printf("tokens->length = %d\n", tokens->length);
					printf("--\n");
				}
				else {
					free_tokens_t(tokens);
					free(tokens);
					ht_destroy(ht);
					fclose(file);
					error_t("invalid argv at: argv[3]");
				}
			}
			
			// reset tokens	
			free_tokens_t(tokens);
			free(tokens);
			tokens = init_tokens_t();
		}
		
		memset(BUFFER_, 0, strlen(BUFFER_));
	}
	
	if (tokens) {
		free_tokens_t(tokens);
		free(tokens);
	}
	
	ht_destroy(ht);
	fclose(file);

	return 0;
}
