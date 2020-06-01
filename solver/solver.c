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
    while (scanf("%d", &value) != EOF){
       sudoku[x][y] = value;
       y++;
       if(y == 9){
           y = 0;
           x++;
       }
    }
    
    // check if the input puzzle was correctly parsed.
    if(x != 9){
        fprintf(stderr, "Input sudoku was of incorrect format\n");
        for(int i = 0; i < 9; i++){
            free(sudoku[i]);
        }
        free(sudoku);
        return;
    }
 
    print_sudoku(sudoku);

    printf("\n");
    printf("\n");
    solve_sudoku(sudoku);
    printf("\n");
    print_sudoku(sudoku);

}