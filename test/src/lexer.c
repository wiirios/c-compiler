#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/reader.h"
#include "../include/utils.h"

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

void scan_t(char *phrase, int *block, tokens_t *tokens) {
	token_t *token;
	int value, i;	
	extern int *ptr_phrase_type;
	char BUFFER[strlen(phrase) + 1];
	
	//if (!tokens) tokens = init_tokens_t();
	//if(*phrase != ' ' && *phrase != '\n' && *phrase != '\0') tokens->length+=1;
	
	value = i = 0;
		
	if (isdigit(*phrase)) goto is_num;
	
	if (isalpha(*phrase) && (!IS_OPERATOR(*phrase) || !IS_PUNCTUATORS(*phrase))) goto is_char;
	
	if (IS_OPERATOR(*phrase) || IS_PUNCTUATORS(*phrase) || IS_ASSIGNMENT(*phrase) || IS_LOGICAL(*phrase) || IS_SEMICOLON(*phrase) || IS_ASSIGNMENT(*phrase)) goto is_signal;
	
	return;
	
	is_assignment:
		memcpy(BUFFER, phrase, strlen(phrase) + 1);
		token = init_token_t("ASSIGNMENT", &BUFFER, block, ASSIGMENT_ENUM);
		
		memset(BUFFER, 0, strlen(BUFFER));
		print_token_t(token);
		free_token_t(token);
		tokens->length+=1;
		
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
		tokens->array_tokens[tokens->length] = token;
		tokens->length+=1;		
		
		return;
		
	is_char:
		// ignore for now...
		
		//if (*ptr_phrase_type > 0) {
			//token = init_token_t(PRIMITIVE_DATA_TYPES_C[*ptr_phrase_type], &value, block, TYPE_C[*ptr_phrase_type]);
			//return;
		//}
		memcpy(BUFFER, phrase, strlen(phrase) + 1);
			
		if (IS_RESERVED_WORD(BUFFER)) {
			int i = 0;
			
			for (; i < strlen(BUFFER); i++) BUFFER[i] = toupper((unsigned char)BUFFER[i]);			
			
			token = init_token_t(BUFFER, &BUFFER, block, RESERVED_ENUM);
			memset(BUFFER, 0, strlen(BUFFER));
			
			tokens->array_tokens[tokens->length] = token;		
			print_token_t(token);
			
			tokens->length+=1;
			return;
		}
			
		token = init_token_t("CHAR", &BUFFER, block, CHAR_ENUM);
		memset(BUFFER, 0, strlen(BUFFER));
		
		print_token_t(token);
		tokens->array_tokens[tokens->length] = token;
		
		tokens->length+=1;
		return;
		
	is_signal:
		memcpy(BUFFER, phrase, strlen(phrase) + 1);
		
		if (IS_OPERATOR(*phrase)) token = init_token_t("OPERATOR", &BUFFER, block, OPERATOR_ENUM);
		else if (IS_PUNCTUATORS(*phrase)) token = init_token_t("PUNCTUATORS", &BUFFER, block, PUNCTUATORS_ENUM);
		else if (IS_ASSIGNMENT(*phrase)) token = init_token_t("ASSIGNMENT", &BUFFER, block, ASSIGMENT_ENUM);
		else if (IS_LOGICAL(*phrase)) token = init_token_t("LOGICAL", &BUFFER, block, LOGICAL_ENUM);
		else if (IS_SEMICOLON(*phrase)) token = init_token_t("SEMICOLON", &BUFFER, block, SEMICOLON_ENUM);
		else if (IS_ASSIGNMENT(*phrase)) token = init_token_t("ASSIGNMENT", &BUFFER, block, ASSIGMENT_ENUM);
		
		memset(BUFFER, 0, strlen(BUFFER));
		print_token_t(token);
		tokens->array_tokens[tokens->length] = token;
		
		tokens->length+=1;
		return;
}

int get_phrase_type(char *buffer) {	
	if (strcmp(buffer, PRIMITIVE_DATA_TYPES_C[INTEGER_PRIMITIVE_DATA_TYPE]) == 0) return 1;
	else if(strcmp(buffer, PRIMITIVE_DATA_TYPES_C[CHAR_PRIMITIVE_DATA_TYPE]) == 0) return 2;
	else if (strcmp(buffer, PRIMITIVE_DATA_TYPES_C[FLOAT_PRIMITIVE_DATA_TYPE]) == 0) return 3;
	else if (strcmp(buffer, PRIMITIVE_DATA_TYPES_C[LONG_PRIMITIVE_DATA_TYPE]) == 0) return 4;
	
	return 0;
}

