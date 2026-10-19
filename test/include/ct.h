#ifndef CT_HEADER
#define CT_HEADER

#define DEFAULT_PATH "../build/./cc"
#define EXP_FILE "exp"

struct phrases;

struct phrases {
	char input[64];
	char exp[64];
};

void run(struct phrases phrases_);

int read_exp(char *file_name, char *input, char *exp);
int assert(char *exp, char *output);

#endif
