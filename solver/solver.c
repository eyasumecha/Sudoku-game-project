#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "common.h"

void sudoku_solver()
{
    int sudoku[9][9]= {0};
    int value;
    int row = 0, col = 0;

    while (scanf("%d", &value) != EOF && row < 9) {
       sudoku[row][col] = value;
       if (++col >= 9) {
           col = 0;
           row += 1;
       }
    }
    
    // check if the input puzzle was correctly parsed.
    if (row != 9) {
        fprintf(stderr, "Input sudoku was of incorrect format. Exiting...\n");
        return;
    }

    #ifdef DEBUG
        printf("\nSolver parsed sudoku puzzle:\n");
        print_sudoku(sudoku);
    #endif

    int solution[9][9] = {0};
    int ret = unique_solver(sudoku, solution);
    
    #ifdef DEBUG
        printf("\nSolved sudoku:\n");
    #endif

    if (ret == 0) {
        printf("No solutions found.\n");
    } else {
        print_sudoku(solution);
        if (ret == 2)
            printf("Multiple solutions found.\n");
    } 
}

