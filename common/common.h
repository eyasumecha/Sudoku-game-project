/*
 * common.h - header file for common functions between
 * the solver and creator sudoku modules 
 * 
 * Pratinav Bagla, Wendell Wu, and Eyasu Fetene 
 *  May 29 2020
 */

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


/*********print_sudoku**********/
/* print the sudoku puzzel
 * 
 * Caller provides:
 *  valid pointer to a 2D array
 * We return:
 *  the 2D array printed in a 9 by 9 grid
 */
void print_sudoku(int **array);


/********row_checker***************/
/* Check if there is no other number along the row equals
 * to the given value
 * Caller provides:
 *  valid pointer to array, row to be checked, and value to check
 * We return:
 *  true if the value doesn't exist in the row
 *  false if the value does exist  
 */
bool row_checker(int **array, int row, int value);

/*********** column_checker ********************/
/* Check if there is no other number along the column equaling    
 *  the given value
 * Caller provides:  
 *  valid pointer to array, column to be checked, and value to check
 * We return:
 *  true if the value doesn't exist in the row
 *  false if the values doesn't exist
 */
bool column_checker(int **array, int column, int value);

/*********** box_checker *************/
/* Check if there is another number along the corresponsing box 
 * of the given column and row
 * Caller provides:
 *  valid pointer to array, column and row to be checked, and value to check with
 * We return:
 *  true if the value doesn't exist in the box
 *  false if the value exists  
 */
bool box_checker(int **array, int row, int column, int value);

/*********** solve_sudoku ***************/
/* Solve the sudoku puzzel given a 2D array
 * Caller provides:
 *  valid pointer to an unsolved array
 * We return:
 *  the solved version of the 2D array
 */
bool solve_sudoku(int **array);

#endif
