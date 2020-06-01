/*
 * common.c - module for solver and creator modules of 
 * sudoku puzzle
 * 
 * see common.h for more information 
 * 
 * Pratinav Bagla, Wendell Wu, and Eyasu Fetene 
 * May 29, 2020
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

static void unique_solver_helper(int **temp, int **firstSolution, int *numSolutions);

void print_sudoku(int **array){

    for(int i = 0; i < 9; i++){        // iterate through the 9 arrays in the pointer
        for(int j = 0; j < 9; j++){    // iterate through the 9 elements in the current array
            printf("%d ", array[i][j]); // print out the number
        }
        printf("\n"); //start at a new line after printing first array 
    }
}

bool row_checker(int **array, int row, int value){
    for(int i = 0; i < 9; i++){  //iterate through the current row or index of the array
        if(array[row][i] == value){  //check if any of the elements equal given value 
            return false;              // return false if any equal
        }
    }

    return true;   //return true if non equal 
}

bool column_checker(int **array, int column, int value){
    for(int i = 0; i < 9; i++){     //iterate through the current column or index of the array
        if(array[i][column] == value){  //check if any of the elements equal given value 
            return false;                // return false if any equal          
        }
    }

    return true;        //return true if non equal 
}

bool box_checker(int **array, int row, int column, int value){
    int startRow = row - (row % 3);            //find the starting column and row of the box 
    int startColumn = column - (column % 3);

    for(int i = 0; i < 3; i++){     //iterate through that box and check if any equal value 
        for(int j = 0; j < 3; j++){
            if(array[i + startRow][j + startColumn] == value)
            return false;               // return false if any equal those values 
        }
    }

    return true;       //return true if non equal the value in the box
}

bool solve_sudoku(int **array){
    int row = 10, column = 10;

    for(int i = 0; i < 9; i++){         //take in an array and find the immediate empty spot
        for(int j = 0; j < 9; j++){
            if(array[i][j] == 0){
                row = i;
                column = j;
                i = 9;
                j = 9;
                break;
            }
        }
    }

    if( row == 10){    //if inital row value unchanged then return true
        return true;   //meaning puzzel is solved 
    }

    for(int z = 1; z < 10; z++){    //if empty spot found 
        if(box_checker(array, row, column, z) && column_checker(array, column, z) && row_checker(array, row, z))
        {                               //iterate through the possible 9 values and check if they 
            array[row][column] = z;     //pass the box, row, and column requirments 
            printf("\n");               // if so update the value 
            print_sudoku(array);

            if(solve_sudoku(array)){   //recursively call the solve module on the next empty spot
                return true;
            }

            array[row][column] = 0;   //if the recursively called falls out, back track and try with 
        }                               // a new value 
    }

    return false;                   //return false if value couldn't be found for the current spot
}

int unique_solver(int **puzzle, int **firstSolution){
    return 1;
    
    if(puzzle == NULL){
        return 0;
    }

    // initialize temp array and copy puzzle into it for solving purposes
    int **temp = (int **) calloc(9, sizeof(int *));
    for(int i = 0; i < 9; i++){
        temp[i] = (int *) calloc(9, sizeof(int));
        for(int j = 0; j < 9; j++){
            temp[i][j] = puzzle[i][j];
        }
    }

    int numSolutions = 0; // serve as an accumulator to detect non-unique solution
    unique_solver_helper(temp, firstSolution, &numSolutions);

    // clean up
    for(int i = 0; i < 9; i++){
        free(temp[i]);
    }
    free(temp);
}

//TODO
static void unique_solver_helper(int **temp, int **firstSolution, int *numSolutions){
    int row = 10, column = 10;

    for(int i = 0; i < 9; i++){         //take in an array and find the next empty spot
        for(int j = 0; j < 9; j++){
            if(temp[i][j] == 0){
                row = i;
                column = j;
                i = 9;
                j = 9;
                break;
            }
        }
    }
}