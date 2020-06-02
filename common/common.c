/*
 * common.c - module for solver and creator modules of 
 * sudoku puzzle
 * 
 * see common.h for more information 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/**************** LOCAL FUNCTION PROTOTYPES ****************/
static bool unique_solver_helper(int temp[9][9], int first_solution[9][9], int *num_solutions);
static bool row_checker(int array[9][9], int row, int value);
static bool column_checker(int array[9][9], int column, int value);
static bool box_checker(int array[9][9], int row, int column, int value);

/**************** GLOBAL FUNCTIONS ****************/

void print_sudoku(int array[9][9])
{
    for (int i = 0; i < 9; i++) {           // iterate through the 9 arrays in the pointer
        for (int j = 0; j < 9; j++) {       // iterate through the 9 elements in the current array
            printf("%d", array[i][j]);      // print out the number
            if (j != 8) printf(" ");
        }
        printf("\n");                       // start at a new line after printing first array 
    }
}

int unique_solver(int puzzle[9][9], int first_solution[9][9])
{
    // copy puzzle to temp variable
    int temp[9][9] = {0};
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            temp[i][j] = puzzle[i][j];
    int num_solutions = 0;           // serve as an accumulator to detect non-unique solution
    unique_solver_helper(temp, first_solution, &num_solutions);
    return num_solutions;
}

/**************** mycalloc ****************/
/*
 * Behaves like calloc but exits when returns NULL.
 */
void * mycalloc(const size_t nmemb, const size_t size)
{
    void *ptr = calloc(nmemb, size);
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: MALLOC FAILED\n");
        exit(99);
    }
    return ptr;
}

/**************** LOCAL FUNCTIONS ****************/

/**************** unique_solver_helper ****************/
/*
 * Recursive helper function for unique_solver.
 * Logic is documented in-line.
 */
static bool unique_solver_helper(int temp[9][9], int first_solution[9][9], int *num_solutions)
{
    int row = 9, col = 9;

    // find the next empty spot in the array;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (temp[i][j] == 0) {
                row = i;
                col = j;
                break;
            }
        }
    }

    // if no empty spots found, increment num_solutions and return appropriate bool
    if (row == 9) {
        (*num_solutions)++;
        if (*num_solutions == 1 && first_solution != NULL) { // if this is the first solution, copy to first_solution
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    first_solution[i][j] = temp[i][j];
        } else if (*num_solutions > 1) { // if this is the second solution, don't do anything, return 2 to stop recursion.
            return false;
        }
        return true;
    }

    // empty spot was found
    for (int i = 1; i <= 9; i++) {
        // if the number 'i' satisfies the rules for its spot, 
        if (box_checker(temp, row, col, i) && column_checker(temp, col, i) && row_checker(temp, row, i)) {
            // set that spot to 'i'
            temp[row][col] = i;

            // if second solution found, stop recursing
            if (!unique_solver_helper(temp, first_solution, num_solutions))
                return false;
            else // otherwise, reset to 0 and try more numbers
                temp[row][col] = 0;
        }
    }

    //no numbers worked for that spot, keep trying to look for more possibilities before
    return true;
}

/**************** row_checker ****************/
/* Check if there is no other number along the row equals
 * to the given value
 * Caller provides:
 *  valid pointer to array, row to be checked, and value to check
 * We return:
 *  true if the value doesn't exist in the row
 *  false if the value does exist  
 */
static bool row_checker(int array[9][9], int row, int value)
{
    for (int i = 0; i < 9; i++) {  //iterate through the current row or index of the array
        if (array[row][i] == value) {  //check if any of the elements equal given value 
            return false;              // return false if any equal
        }
    }

    return true;   //return true if non equal 
}

/**************** column_checker ****************/
/* Check if there is no other number along the column equaling    
 *  the given value
 * Caller provides:  
 *  valid pointer to array, column to be checked, and value to check
 * We return:
 *  true if the value doesn't exist in the row
 *  false if the values doesn't exist
 */
static bool column_checker(int array[9][9], int column, int value)
{
    for (int i = 0; i < 9; i++) {     //iterate through the current column or index of the array
        if (array[i][column] == value) {  //check if any of the elements equal given value 
            return false;                // return false if any equal          
        }
    }

    return true;        //return true if non equal 
}

/**************** box_checker ****************/
/* Check if there is another number along the corresponsing box 
 * of the given column and row
 * Caller provides:
 *  valid pointer to array, column and row to be checked, and value to check with
 * We return:
 *  true if the value doesn't exist in the box
 *  false if the value exists  
 */
static bool box_checker(int array[9][9], int row, int column, int value)
{
    int startRow = row - (row % 3);            //find the starting column and row of the box 
    int startColumn = column - (column % 3);

    for (int i = 0; i < 3; i++) {     //iterate through that box and check if any equal value 
        for (int j = 0; j < 3; j++) {
            if (array[i + startRow][j + startColumn] == value)
            return false;               // return false if any equal those values 
        }
    }

    return true;       //return true if non equal the value in the box
}

