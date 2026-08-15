#include "../include/lexer.h"

void scan_t(char *phrase, int *block) {
	int value = 0;
	token_t *token;
		
	if (IS_OPERATOR(*phrase)) goto is_operator;
		
	while (isdigit(*phrase)) {
		value = 10 * value + (*phrase - '0'); 
	
		phrase++;
	}
	
	token = init_token_t("INT", value, block);
	print_token_t(token);
	free_token_t(token);
	
	return;
	
	is_operator:			
		token = init_token_t("OPERATOR", (*phrase - '0'), NULL);
		print_token_t(token);
		free_token_t(token);
}
