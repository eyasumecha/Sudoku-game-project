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

static void swap3col(int **puzzle);
static void swapcol(int **puzzle);
static void swap3row(int **puzzle);
static void swaprow(int **puzzle);

/**
 * This function is called by program execution
 *  if "create" was called. It takes in no parameters
 *  and does not return anything. It simply creates
 *  a puzzle guaranteed to have a unique solution and
 *  prints it to stdout.
 */
void create_puzzle(){
    int puzzle[9][9] = {{4, 3, 5, 2, 6, 9, 7, 8, 1},
                        {6, 8, 2, 5, 7, 1, 4, 9, 3},
                        {1, 9, 7, 8, 3, 4, 5, 6, 2},
                        
                        {8, 2, 6, 1, 9, 5, 3, 4, 7},
                        {3, 7, 4, 6, 8, 2, 9, 1, 5},
                        {9, 5, 1, 7, 4, 3, 6, 2, 8},
                        
                        {5, 1, 9, 3, 2, 6, 8, 7, 4},
                        {2, 4, 8, 9, 5, 7, 1, 3, 6},
                        {7, 6, 3, 4, 1, 8, 2, 5, 9}};

    srand(time(0));
    shuffle(puzzle);
    
    
    
    int n;
    time_t t;

    //seed it
    n = 5;
    
    for(int i = 0; i < n; i++){
        printf("%d\n", rand()%50);
    }
}

static void shuffle(int **puzzle){
    shuffle_col(puzzle);
    shuffle_row(puzzle);
}

static void shuffle_col(int **puzzle){
    // shuffle the three "major" columns in the board
    for(int i = 0; i < NUM_SHUFFLES; i++){
        int col1 = 
    }
}

static void shuffle_row(int **puzzle){
    
}