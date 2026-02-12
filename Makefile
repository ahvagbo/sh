# fuckass makefile for my shell

CC=gcc
CFLAGS=-Wall -O2 -Wextra -g

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXEC=sh

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean

