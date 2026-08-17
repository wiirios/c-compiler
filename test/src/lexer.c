#include "../include/lexer.h"

char *PRIMITIVE_DATA_TYPES_C[] = {
	"int",
	"char",
	"float",
	"long"
};

int TYPE_C[] = {
	INTEGER_ENUM,
	CHAR_ENUM,
	FLOAT_ENUM,
	LONG_ENUM,
};

void scan_t(char *phrase, int *block) {
	token_t *token;
	int value, i;
	extern int *ptr_phrase_type;
	char BUFFER[strlen(phrase) + 1];
	
	value = i = 0;

	if (isdigit(*phrase)) goto is_num;
	
	if (isalpha(*phrase) && (!IS_OPERATOR(*phrase) || !IS_PUNCTUATORS(*phrase))) goto is_char;
	
	if (IS_OPERATOR(*phrase) || IS_PUNCTUATORS(*phrase)) goto not_num;
	
	return;
	
	is_num:
		while (*phrase) {
			if (!isdigit(*phrase)) {
				printf("bad character: %c\n", *phrase);
				error_t("bad character found while reading a integer");
			}
			
			value = 10 * value + (*phrase - '0');
			phrase++;
		}
			
		token = init_token_t("INT", &value, block, INTEGER_ENUM);
		print_token_t(token);
		free_token_t(token);
		
		return;
		
	is_char:
		// ignore for now...
		
		//if (*ptr_phrase_type > 0) {
			//token = init_token_t(PRIMITIVE_DATA_TYPES_C[*ptr_phrase_type], &value, block, TYPE_C[*ptr_phrase_type]);
			//return;
		//}
		memcpy(BUFFER, phrase, strlen(phrase) + 1);
				
		token = init_token_t("CHAR", &BUFFER, block, CHAR_ENUM);
		memset(BUFFER, 0, strlen(BUFFER));
		print_token_t(token);
		free_token_t(token);
				
		return;
		
	not_num:
		if (__clang__) {
			;
		}
		int signal = *phrase;
		
		token = init_token_t(IS_OPERATOR(*phrase) ? "OPERATOR": "PUNCTUATORS", &signal, block, IS_OPERATOR(*phrase) ? OPERATOR_ENUM: PUNCTUATORS_ENUM);
		print_token_t(token);
		free_token_t(token);
		
		return;
}

int get_phrase_type(char *buffer) {	
	if (strcmp(buffer, PRIMITIVE_DATA_TYPES_C[INTEGER_PRIMITIVE_DATA_TYPE]) == 0) return 1;
	else if(strcmp(buffer, PRIMITIVE_DATA_TYPES_C[CHAR_PRIMITIVE_DATA_TYPE]) == 0) return 2;
	else if (strcmp(buffer, PRIMITIVE_DATA_TYPES_C[FLOAT_PRIMITIVE_DATA_TYPE]) == 0) return 3;
	else if (strcmp(buffer, PRIMITIVE_DATA_TYPES_C[LONG_PRIMITIVE_DATA_TYPE]) == 0) return 4;
	
	return 0;
}

