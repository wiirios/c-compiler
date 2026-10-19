C = clang
NAME = ct
SRC = main.c src/ct.c src/utils.c
SRC_GDB = main.c -g main.c src/ct.c utils.c
SRC_WARNINGS = main.c -Wall -Wextra main.c src/ct.c utils.c

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
	rm ct
