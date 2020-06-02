#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "common.h"

void solver(){
    int **sudoku = (int **)malloc(9 * sizeof(int*));
    for(int i = 0; i < 9; i++){
        sudoku[i] = (int *)malloc(9 * sizeof(int));
    }
    int value;
    int x =0, y = 0;
    while (scanf("%d", &value) != EOF && x < 9){
       sudoku[x][y] = value;
       y++;
       if(y == 9){
           y = 0;
           x++;
       }
    }
    
    // check if the input puzzle was correctly parsed.
    if(x != 9){
        fprintf(stderr, "Input sudoku was of incorrect format. Exiting...\n");
        for(int i = 0; i < 9; i++){
            free(sudoku[i]);
        }
        free(sudoku);
        return;
    }

    //create some memory to hold the solution
    int **solution = (int **) calloc(9, sizeof(int *));
    for(int i = 0; i < 9; i++){
        solution[i] = (int *) calloc(9, sizeof(int));
    }

    #ifdef DEBUG
        printf("\nSolver parsed sudoku puzzle:\n");
        print_sudoku(sudoku);
    #endif

    int ret = unique_solver(sudoku, solution);
    
    #ifdef DEBUG
        printf("\nSolved sudoku:\n");
    #endif

    if(ret == 0){
        printf("No solutions found.\n");
    }else{
        print_sudoku(solution);
        if(ret == 2)
            printf("Multiple solutions found.\n");
    }
    
    //clean up memory
    for(int i = 0; i < 9; i++){
        free(solution[i]);
    }
    free(solution);
    for(int i = 0; i < 9; i++){
        free(sudoku[i]);
    }
    free(sudoku);
}