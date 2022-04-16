# Copyright 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)

CC=gcc
CFLAGS=-I -Wall -Wextra -std=c99
DEPS=tema1.c doubly_linked_list.h op_utils.h

OBJ := op_utils.o
OBJ += doubly_linked_list.o

build: tema1

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

tema1: $(OBJ) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o tema1