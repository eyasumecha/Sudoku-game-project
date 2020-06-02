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
    int check = 1;
    print_sudoku(sudoku);
    solve_sudoku(sudoku, &check);
    
}


int main(){
    solver();

    return 0;
}