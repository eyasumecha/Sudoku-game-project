# Makefile for the creator module
#
# CS50 Final Project

C = ../common
R = ../creator
S = ../solver

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C -I$R -I$S
PROG = sudoku
OBJS = sudoku.o $C/common.o $R/creator.o $S/solver.o
# Comment or uncomment the below statement to enable/disable debug printing.
#DEBUG = -D DEBUG

# executable depends on object files
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# object files depend on include files
sudoku.o: $C/common.h $R/creator.h $S/solver.h
	$(CC) $(CFLAGS) -c -o sudoku.o sudoku.c $(DEBUG)

$R/creator.o: $C/common.h $R/creator.h
	$(CC) $(CFLAGS) -c -o $@ $R/creator.c $(DEBUG)

$S/solver.o: $C/common.h $S/solver.h
	$(CC) $(CFLAGS) -c -o $@ $S/solver.c $(DEBUG)

$C/common.o: $C/common.h
	$(CC) $(CFLAGS) -c -o $@ $C/common.c $(DEBUG)

.PHONY: clean test valgrind

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM

test:

valgrind: