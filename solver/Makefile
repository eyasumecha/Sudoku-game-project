# Makefile for 'solver' module 

# DEBUG = -D DEBUG
C = ../common
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C $(DEBUG)
CC = gcc

#rules
solver.o: ../common/common.h solver.h solver.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f *~ *.o *.dSYM
