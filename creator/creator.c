/**
 * Eyasu Lemma, Pratinav Bagla, and Wendell Wu
 * CS50 Final Project - Sudoku Creator Module
 * 5/31/20
 * 
 * This module is responsible for creating a new randomized sudoku puzzle which
 * only has 1 unique solution and has a minimum of 40 numbers removed.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "common.h"

#define NUM_SHUFFLES 20

static void shuffle(int **puzzle);
static void shuffle_col(int **puzzle);
static void shuffle_row(int **puzzle);

static void swap3col(int **puzzle, int col1, int col2);
static void swapcol(int **puzzle, int col1, int col2);
static void swap3row(int **puzzle, int row1, int row2);
static void swaprow(int **puzzle, int row1, int row2);

static void remove_nums(int **puzzle);

/**
 * This function is called by program execution
 *  if "create" was called. It takes in no parameters
 *  and does not return anything. It simply creates
 *  a puzzle guaranteed to have a unique solution and
 *  prints it to stdout.
 */
void create_puzzle(){
    // hardcoded template to work off of, where [0][0] = top left and [8][0] is bottom left. Essentially, [row][col]
    int template[9][9] = {{4, 3, 5, 2, 6, 9, 7, 8, 1},
                        {6, 8, 2, 5, 7, 1, 4, 9, 3},
                        {1, 9, 7, 8, 3, 4, 5, 6, 2},
                            
                        {8, 2, 6, 1, 9, 5, 3, 4, 7},
                        {3, 7, 4, 6, 8, 2, 9, 1, 5},
                        {9, 5, 1, 7, 4, 3, 6, 2, 8},
                            
                        {5, 1, 9, 3, 2, 6, 8, 7, 4},
                        {2, 4, 8, 9, 5, 7, 1, 3, 6},
                        {7, 6, 3, 4, 1, 8, 2, 5, 9}};

    int **puzzle = (int **) calloc(9, sizeof(int *));
    for(int i = 0; i < 9; i++){
        puzzle[i] = (int *) calloc(9, sizeof(int));
        for(int j = 0; j < 9; j++){
            puzzle[i][j] = template[i][j];
        }
    }

    #ifdef DEBUG
        printf("Template board:\n");
        print_sudoku(puzzle);
    #endif

    // seed the RNG and shuffle the puzzle around.
    srand(time(0));
    shuffle(puzzle);
    
    #ifdef DEBUG
        printf("\nShuffled template board:\n");
        print_sudoku(puzzle);
    #endif

    remove_nums(puzzle);
    #ifdef DEBUG
        printf("\nBoard with nums removed:\n");
    #endif
    print_sudoku(puzzle);

    for(int i = 0; i < 9; i++){
        free(puzzle[i]);
    }
    free(puzzle);
}

/**
 * Shuffler functions. Calls swap functions as needed, and uses rand() to generate
 * random col and row numbers to swap. Random seed must be set before using these functions.
 * 
 * Shuffles the puzzle around but guarantees that the puzzle
 * still abides by the sudoku rules. Directly edits
 * the puzzle which is passed in.
 */
static void shuffle(int *puzzle[]){
    shuffle_col(puzzle);
    shuffle_row(puzzle);
}
static void shuffle_col(int **puzzle){
    // shuffle the three "major" columns in the board, each 9x3 column
    for(int i = 0; i < NUM_SHUFFLES; i++){
        int col1 = rand() % 3, col2 = rand() % 3;
        swap3col(puzzle, col1, col2);
    }

    // pick one of the three "major" columns, and shuffle their inner 9x1 columns within the major column
    for(int i = 0; i < 2*NUM_SHUFFLES; i++){
        int section = rand() % 3;
        int col1 = section * 3 + (rand() % 3), col2 = section * 3 + (rand() % 3);
        swapcol(puzzle, col1, col2);
    }
}
static void shuffle_row(int **puzzle){
    // shuffle the three "major" rows in the board, each 3x9 row
    for(int i = 0; i < NUM_SHUFFLES; i++){
        int row1 = rand() % 3, row2 = rand() % 3;
        swap3row(puzzle, row1, row2);
    }

    // pick one of the three "major" rows, and shuffle their inner 1x9 rows within the major row
    for(int i = 0; i < 2 * NUM_SHUFFLES; i++){
        int section = rand() % 3;
        int row1 = section * 3 + (rand() % 3), row2 = section * 3 + (rand() % 3);
        swaprow(puzzle, row1, row2);
    }
}

/**
 * Swapper functions - swap3 will swap 3 columns/rows at a time, where 1 and 2 are the section numbers.
 */
static void swap3col(int **puzzle, int col1, int col2){
    if(col1 == col2) return;
    for(int i = 0; i < 3; i++){
        swapcol(puzzle, col1*3 + i, col2*3 + i);
    }
}
static void swapcol(int **puzzle, int col1, int col2){
    if(col1 == col2) return;
    int temp = 0;
    for(int i = 0; i < 9; i++){
        temp = puzzle[i][col1];
        puzzle[i][col1] = puzzle[i][col2];
        puzzle[i][col2] = temp;
    }
}
static void swap3row(int **puzzle, int row1, int row2){
    if(row1 == row2) return;
    for(int i = 0; i < 3; i++){
        swaprow(puzzle, row1*3 + i, row2*3 + i);
    }
}
static void swaprow(int **puzzle, int row1, int row2){
    if(row1 == row2) return;
    int temp = 0;
    for(int j = 0; j < 9; j++){
        temp = puzzle[row1][j];
        puzzle[row1][j] = puzzle[row2][j];
        puzzle[row2][j] = temp;
    }
}

/**
 * Takes in a solved (filled) puzzle and removes
 * 40 random numbers s.t. there is still only one
 * unique solution to the puzzle. Random must be
 * seeded before calling this function.
 * Parameters and returns:
 * It directly edits the given puzzle by setting any
 * removed numbers to 0 and does not
 * return anything.
 */
static void remove_nums(int **puzzle){
    int removedCount = 0;

    int row, col;
    while(removedCount < 40){
        row = rand() % 9;
        col = rand() % 9;
        while(puzzle[row][col] == 0){ // make sure the num isn't already removed
            row = rand() % 9;
            col = rand() % 9;
        }
        #ifdef DEBUG
            printf("Trying to remove spot [%d][%d]\nNumremoved so far: %d\n", row, col, removedCount);
        #endif
        int temp = puzzle[row][col];
        puzzle[row][col] = 0;
        int numSolutions = unique_solver(puzzle, NULL);
        if(numSolutions != 1){ // if non-unique solution or non-existent solution
            puzzle[row][col] = temp; // put the number back and continue
            #ifdef DEBUG
                printf("Failed to remove.\n");
            #endif
        }else{
            removedCount++; // keep the 0 and increment removedCount
            #ifdef DEBUG
                printf("Removed successfully!\n");
            #endif
        }
    }
}