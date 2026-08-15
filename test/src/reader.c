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

