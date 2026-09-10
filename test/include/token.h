#ifndef TOKEN_HEADER
#define TOKEN_HEADER

#define SHOW_TYPE_TOKEN 0
#define TYPES_LENGTH 8
#define MAX_TOKENS 32
#define MAX_PANIC_TOKEN_MSG_LENGTH 1024

enum TYPE {
	INTEGER_ENUM,			// 0
	CHAR_ENUM,				// 1
	FLOAT_ENUM,				// 2
	LONG_ENUM,				// 3
	OPERATOR_ENUM,			// 4
	PUNCTUATORS_ENUM,		// 5
	ASSIGMENT_ENUM,			// 6
	LOGICAL_ENUM,			// 7
	RESERVED_ENUM,			// 8
	SEMICOLON_ENUM			// 9
};

enum TOKEN_RESERVED_KEYWORD {
	IF_TOKEN,
	ELSE_TOKEN,
	FOR_TOKEN,
	WHILE_TOKEN,
};

typedef struct token token_t;
typedef struct tokens tokens_t;

struct panic {
	char msg[MAX_PANIC_TOKEN_MSG_LENGTH];
	int error;
};

struct token {
	char *identifier;
	void *value;
	int block;
	enum TYPE type;
	struct panic panic_s;
};

struct tokens {
	token_t *array_tokens[MAX_TOKENS];
	int length;
};

token_t *init_token_t(char *identifier, void *value, int *block, enum TYPE type);

tokens_t *init_tokens_t();

int print_token_t(token_t *token);
int get_token_block(token_t *token);
int get_tokens_length(tokens_t *tokens);

void free_token_t(token_t *token);
void free_tokens_t(tokens_t *tokens);

#endif
