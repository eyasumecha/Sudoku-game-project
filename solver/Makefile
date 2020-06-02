# Makefile for 'solver' module 

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../common
CC = gcc
# DEBUG = -D DEBUG

#rules
solver.o: ../common/common.o solver.c 
	$(CC) $(CFLAGS) $^ -c -o $@ $(DEBUG)

clean:
	rm -f *~ *.o *.dSYM
