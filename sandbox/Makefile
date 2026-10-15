C = clang
NAME = cc
SRC = main.c src/lexer.c src/reader.c src/token.c src/utils.c src/hashtable.c src/parser.c src/dock.c
SRC_GDB = main.c -g src/lexer.c src/reader.c src/token.c src/utils.c src/hashtable.c src/parser.c src/dock.c
SRC_WARNINGS = main.c -Wall -Wextra src/lexer.c src/reader.c src/token.c src/utils.c src/hashtable.c src/parser.c src/dock.c

all:
	$(C) $(SRC) -o $(NAME)

alld:
	$(C) $(SRC_GDB) -o $(NAME)

allw:
	$(C) $(SRC_WARNINGS) -o $(NAME)

install: all
	@echo "buid complete"

debug: alld
	@echo "buid [debug] complete"

war: allw
	@echo "buid [warnings] complete"

clean:
	rm cc
