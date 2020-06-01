# Makefile for 'solver' module 

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common
CC = gcc

#rules
solver: ../common/common.o solver.c 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *~ *.o *.dSYM