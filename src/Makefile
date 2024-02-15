CC = gcc
CFLAGS = -Wall -Wextra -Werror -ncurses -std=11
PTH = ../build/game

all: game

game: game_of_life.c
	$(CC) $(CFLAGS) game_of_life.c -o $(PTH)

clean:
	rm -rf $(PTH)

rebuilf: clean all