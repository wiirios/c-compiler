#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdint.h>

#include "include/token.h"
#include "include/utils.h"
#include "include/reader.h"
#include "include/hashtable.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/dock.h"

static int i = 0;
static int block = 0;
static int phrase_type = -1;
static int assignment = 0;
ht_t *ht = NULL;
dock_t *dock = NULL;

int *ptr_phrase_type = &phrase_type;

int main(int argc, char *argv[]) {
	if (argc < 2) error_t("no input files\nusage: " 
	"./cc [-t] [-y] source_file\n-t, shows the tokenization process\n-y, shows the token types\nsource_file, file to be compiled");

	static struct option long_options[] = {
        {"token", no_argument, 0, 't'},
        {"type",  no_argument, 0, 'y'},
        {0, 0, 0, 0}
    };

	uint8_t pp = 0;
    int flag_t = 1 << 0;
    int flag_y = 1 << 1;
    int opt;
    int long_ind = 0;
    
    while ((opt = getopt_long(argc, argv, "ty", long_options, &long_ind)) != -1) {
        switch (opt) {
			case 't': pp |= flag_t; break;
			case 'y': pp |= flag_y; break;
			default: error_t("usage: ./cc [-t] [-y] source_file\n-t, shows the tokenization process\n-y, shows the token types\nsource_file, file to be compiled");
		}
    }
	
	FILE *file = get_file_t(argv[optind]);
	
	char BUFFER_[BUFFER_SIZE_T];
	ht = ht_init();
	
	tokens_t *tokens = init_tokens_t();
	dock = init_dock_t(64);
	
	while (feof(file) == 0) {
		reader_file_t(BUFFER_, sizeof(BUFFER_), file, &block);
		scan_t(BUFFER_, &block, tokens);
		
		if (IS_SEMICOLON(BUFFER_[strlen(BUFFER_) - 1]) || IS_PUNCTUATORS(BUFFER_[strlen(BUFFER_) - 1])) {
			if (pp & flag_y) for (int i = 0; i < tokens->length; i++) {
				print_token_t(tokens->array_tokens[i], 1);
				printf("\n");	
			}
				
			if (pp & flag_y) printf("----EOF [-y]----\n");
				
			if (pp & flag_t) for (int i = 0; i < tokens->length; i++) print_token_t(tokens->array_tokens[i], 0);
				
			if (pp & flag_t) printf("\n----EOF [-t]----\n");
			
			if (!parser(tokens)) printf("invalid grammar\n");
			else printf("valid grammar\n");
			
			// reset tokens	
			free_tokens_t(tokens);
			free(tokens);
			tokens = init_tokens_t();
			i = 0;
		}
		
		memset(BUFFER_, 0, strlen(BUFFER_));
		i++;
	}
	
	if (tokens) {
		free_tokens_t(tokens);
		free(tokens);
	}
	
	ht_destroy(ht);
	destroy_dock(dock);
	fclose(file);

	return 0;
}
