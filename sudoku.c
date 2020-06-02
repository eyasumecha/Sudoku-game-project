/**
 * CS50 Final Project - Main Function
 * 
 * This is the module which parses parameters and calls the appropriate
 * modules to either solve or create a sudoku puzzle.
 */

#include <string.h>
#include "common.h"
#include "creator.h"
#include "solver.h"


int main(int argc, char *argv[])
{
    const char *USAGE = "Usage: sudoku [create|solve]\n";
    
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments.\n%s", USAGE);
        return 1;
    }

    if (strcmp(argv[1], "create") == 0) {
        sudoku_create();
    } else if (strcmp(argv[1], "solve") == 0) {
        sudoku_solver();
    } else {
        fprintf(stderr, "Argument was not create or solve.\n%s", USAGE);
        return 2;
    }

    return 0;
}

