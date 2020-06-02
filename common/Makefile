# makefile for common module 

CFLAGS = -Wall -pedantic -std=c11 -ggdb  
CC = gcc

# rules
common.o: common.h common.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f *~ *.o *.dSYM
