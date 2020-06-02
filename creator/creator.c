/*
 * CS50 Final Project - Sudoku Creator Module
 * 
 * This module is responsible for creating a new randomized sudoku puzzle which
 * only has 1 unique solution and has a minimum of 40 numbers removed.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "common.h"

static void shuffle(int **puzzle);
static void remove_nums(int **puzzle);
static void get_rand_orientation(int *arr);
static void copy_puzzle(int **og, int **copy);

/**************** sudoku_create ****************/
/*
 * This function is called by program execution if "create" was called. It
 * takes in no parameters and does not return anything. It simply creates a
 * puzzle guaranteed to have a unique solution and prints it to stdout.
 */
void sudoku_create(void)
{
    // Hardcoded template to work off of, where [0][0] = top left and [8][0] is
    // bottom left. Essentially, [row][col].
    int puzzle[9][9] = {
        {4, 3, 5, 2, 6, 9, 7, 8, 1},
        {6, 8, 2, 5, 7, 1, 4, 9, 3},
        {1, 9, 7, 8, 3, 4, 5, 6, 2},
            
        {8, 2, 6, 1, 9, 5, 3, 4, 7},
        {3, 7, 4, 6, 8, 2, 9, 1, 5},
        {9, 5, 1, 7, 4, 3, 6, 2, 8},
            
        {5, 1, 9, 3, 2, 6, 8, 7, 4},
        {2, 4, 8, 9, 5, 7, 1, 3, 6},
        {7, 6, 3, 4, 1, 8, 2, 5, 9}
    };

    // Shuffle the template puzzle to get a new, valid puzzle.
    srand(time(0));     // seed RNG
    shuffle(&puzzle); 

    #ifdef DEBUG
        printf("\nRandomly shuffled template board:\n");
        print_sudoku(puzzle);
    #endif

    // Remove min. 40 slots making sure there is a unique solution.
    remove_nums(&puzzle);
    #ifdef DEBUG
        printf("\nBoard with nums removed:\n");
    #endif
    print_sudoku(&puzzle);
}

/**************** shuffle ****************/
/*
 * Randomly shuffles the given sudoku puzzle while maintaing its validity.
 * Caller must provide a valid pointer to an int[9][9] containing the puzzle.
 * Directly edits the given puzzle.
 */

static void shuffle(int **puzzle)
{
    int puzzle_copy[9][9]= {0};
    int pos_total[2][9] = {0};
    int *cols_copy[9] = {0};
    int pos_major[3]= {0};
    int pos_minor[3]= {0};

    // Randomly generate an int[] of shuffled column positions as well as row
    // positions. The sudoku's validity is maintained by first generating the
    // positions for each major 9x3/3x9 section, then the 9x1/1x9 rows/columns
    // within them.
    for (int i = 0; i < 2; i++) {
        get_rand_orientation(&pos_major);
        for (int j = 0; j < 3; j++) {
            get_rand_orientation(&pos_minor);
            for (int k = 0; k < 3; k++)
                pos_total[i][j * 3 + k] = pos_major[j] * 3 + pos_minor[k];
        }
    }

    // Re-orient the puzzle according to the newly generated int arrays of
    // shuffled col/row positions.

    // Re-orient cols.
    copy_puzzle(puzzle, &puzzle_copy);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            puzzle[j][i] = puzzle_copy[j][pos_total[0][i]];
        }
    }

    // Re-orient rows. No need to make copy of entire 2d array, just of the
    // pointers to each row array.
    for (int i = 0; i < 9; i++)
        cols_copy[i] = puzzle[i];
    for (int i = 0; i < 9; i++)
        puzzle[i] = cols_copy[pos_total[1][i]];
}

/**************** remove_nums ****************/
/*
 * Takes in a solved (filled) puzzle and removes
 * 40 random numbers s.t. there is still only one
 * unique solution to the puzzle. Random must be
 * seeded before calling this function.
 * Parameters and returns:
 * It directly edits the given puzzle by setting any
 * removed numbers to 0 and does not
 * return anything.
 */
static void remove_nums(int **puzzle)
{
    int removedCount = 0;
    int row, col;
    while (removedCount < 40) {
        row = rand() % 9;
        col = rand() % 9;
        while (puzzle[row][col] == 0) {     // make sure the num isn't already removed
            row = rand() % 9;
            col = rand() % 9;
        }
        int temp = puzzle[row][col];
        puzzle[row][col] = 0;
        int numSolutions = unique_solver(puzzle, NULL);
        if (numSolutions != 1) {            // if non-unique solution or non-existent solution
            puzzle[row][col] = temp;        // put the number back and continue
        } else {
            removedCount++;                 // keep the 0 and increment removedCount
        }
    }
}

/**************** get_rand_orientation ****************/
/*
 * Generates an int array of random positions for shuffling the rows and cols in
 * the sudoku, setting it to the given int[]. There are 6 total possibilites:
 * {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}.
 * Caller must provide a valid pointer to an int[].
 * Caller is responsible for seeding srand before calling the function.
 */
static void get_rand_orientation(int *arr)
{
    // generate a random int between 0 and 3 (excluding 3) for each array item.
    for (int i = 0; i < 3; i++) {
        int arr[i] = rand() * 3;
        // if the generated int is already present in the array, repeat.
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                i -= 1;
                break;
            }
        }
    }
}

/**************** copy_puzzle ****************/
/*
 * Copies the given puzzle int[9][9] to the given int[9][9].
 * Caller provides valid pointers to the original and copy arrays.
 */
static void copy_puzzle(int **og, int **copy)
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            copy[i][j] = og[i][j];
}

