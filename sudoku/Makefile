# Makefile for the creator module
#
# CS50 Final Project

C = ../common
R = ../creator
S = ../solver

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$C -I$R -I$S
PROG = sudoku
OBJS = sudoku.o
LLIBS = $C/common.o $R/creator.o $S/solver.o
#DEBUG = -D DEBUG



# executable depends on object files
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ 

# object files depend on include files
sudoku.o: $C/common.h $R/creator.h $S/solver.h
	$(CC) $(CFLAGS) -c -o sudoku.o sudoku.c $(DEBUG)
#alternatively, use $(LLIBS) to be lazy, just include the whole library as dependency.

.PHONY: clean test valgrind

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM

test:

valgrind: