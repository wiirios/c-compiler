#ifndef CT_HEADER
#define CT_HEADER

#define DEFAULT_PATH "../build/./cc"
#define EXP_FILE "exp"

int run(void);
int read_exp(char *file_name, char *input, char *exp);
int assert(char *exp, char *output);

#endif
