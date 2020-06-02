# Makefile for the creator module
#
# CS50 Final Project

C = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C
PROG = creator.o
OBJS = creator.c

# DEBUG = -D DEBUG

# make the object file for creator
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -c -o $@ $(DEBUG)

.PHONY: clean test valgrind

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM

test:

valgrind:
