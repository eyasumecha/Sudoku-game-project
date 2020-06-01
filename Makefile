# Project Root Makefile
# Makefile for CS50 Sudoku Final Project
#
# Wendell Wu, Eyasu Lemma, Pratinav Bagla - June 1st 2020

MAKE = make
.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	$(MAKE) -C common
	$(MAKE) -C creator
	$(MAKE) -C solver
	$(MAKE) -C run

############### TAGS for emacs users ##########
TAGS:  Makefile */Makefile */*.c */*.h */*.md */*.sh
	etags $^

############## clean  ##########
clean:
	rm -f *~
	rm -f TAGS
	$(MAKE) -C common clean
	$(MAKE) -C creator clean
	$(MAKE) -C solver clean
	$(MAKE) -C run clean
