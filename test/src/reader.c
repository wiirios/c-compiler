#include "../include/reader.h"

void reader_file_t(char *BUFFER_, size_t sizebuffer, FILE *file, int *block) {
	int peek, i;
	
	i = 0;
	while ((peek = fgetc(file)) != EOF) {
		
		if (peek != ' ' && (isalnum(peek) || isalpha(peek))) BUFFER_[i] = peek;
		
		if (IS_OPERATOR(peek) || IS_PUNCTUATORS(peek)) {
			BUFFER_[0] = peek;
			BUFFER_[1] = '\0';
			break;	
		}
		
		if (IS_PUNCTUATORS(peek) && peek == '{') *block+=1;
		
		if (IS_PUNCTUATORS(peek) && peek == '}') *block-=1;
		
		if (peek == ' ' && strlen(BUFFER_) == 0) continue;
		
		if (peek == ' ') {
			BUFFER_[i] = '\0';
			break;
		}
		
		i++;
	}
	
}

FILE *get_file_t(const char *file_name) {
		size_t size_file;
		
		if (get_file_size_t(file_name, &size_file) != 0) error_t("Cannot get file size or file size too small to read");
		
		if (strcmp(strrchr(file_name, '.'), ".c") != 0) error_t("Invalid file extension");	
		
		FILE *file = fopen(file_name, "r");
		
		if (!file) error_t("error while open argc 1");
		
		return file;
}

int get_file_size_t(const char *file_name, size_t *out_size) {
    struct stat st;

    if ((stat(file_name, &st)) != 0) return -1;

    if ((size_t) st.st_size > __SIZE_MAX__ || st.st_size <= 1) return -1;

    *out_size = (size_t) st.st_size;

    return 0;
}
