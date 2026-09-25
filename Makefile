CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -Iinclude
SRC=src/main.c src/lexer.c src/comment_remover.c src/whitespace_remover.c
all:
	$(CC) $(CFLAGS) $(SRC) -o comment_tool
clean:
	rm -f comment_tool comment_tool.exe
run: all
	./comment_tool
