# Implementation Spec

## Data structures

Each 9x9 sudoku is represented with a "2 dimensional" 9x9 integer array:
`int puzzle[9][9]`. The first index represents the row, and the second represents the
column. Thus each number is contained in its respective
`puzzle[row_index][column_index]`.

All sudokus are always declared on the stack and not the heap. This is because
the size of the puzzle 2d array is relatively small, and should not cause a
stack overflow on most machines (excluding special cases like embedded systems),
even with multiple puzzle arrays being stored in memory. This seems to be the
simplest, safest, and most efficient choice.

## Main (`sudoku.c`)

`sudoku.c`, contained in the project's top-level directory, is the main driver
of the program that parses command line arguments and initializes other modules.

- Check number of command line arguments via the given argument `int argc`.
    - Exit if not == 2.
- Check argument given to `sudoku` contained in `char *argv[]` at index 1. Use
  `strcmp`.
    - If equals "create", initialize creator by calling `sudoku_create`.
    - Else if equals "solve", initialize solver by calling `sudoku_solve`.
    - Else, print error and exit.

## Creator

Create a random 9x9 sudoku puzzle with at least 40 missing numbers and a
unique solution. Each columnn is separated with a single space and each row with
a newline. Missing numbers are represented with '0'.

Implemented in `creator.c` contained in the `creator` directory. `creator.h`
exports the following function:

```
/**************** sudoku_create ****************/
/*
 * This function is called by program execution if "create" was called. It
 * takes in no parameters and does not return anything. It simply creates a
 * puzzle guaranteed to have a unique solution and prints it to stdout.
 */
void sudoku_create(void);
```

### `sudoku_create`

Prototype: `void sudoku_create(void)`

Essentially the main function exposed to other programs. Initializes other
modules and facilitates control flow.

- Initial setup:
    - Define a 9x9 2d int array to store the sudoku puzzle and initialize it to
      a solved and valid template sudoku.
    - Seed `rand` by calling `srand` and passing in the current time
      (`time(0)`).
- Randomly shuffle the template puzzle while still maintaining the sudoku's
  validity by calling the `shuffle` function with the puzzle as an argument.
- Remove a minimum of 40 numbers from the puzzle while making sure that the
  sudoku has a unique solution by calling `remove_nums` with the puzzle as an
  argument.
- Print the sudoku in the correct format by calling `print_sudoku` in the common
  module with the puzzle as an argument.

### `shuffle`

Prototype: `static void shuffle(int puzzle[9][9])`

Randomly shuffles the given sudoku puzzle while maintaing its validity.
Caller must provide a valid pointer to an `int[9][9]` containing the puzzle.
Directly edits the given puzzle.

The basic idea behind the shuffling function so that it does not violate sudoku
rules is to shuffle rows and columns while maintaining the integrity for each
3x3 box. This is achieved by first shuffling the 3x3 boxes by treating the 9x9
grid as a 3x3 grid composed of sub-grids. Then, shuffling the actual rows and
columns for each 3x3 grid.

The function first computes the new position for each row and each column using
the algorithm described above, storing it in int arrays. Then, the function
re-orients the actual puzzle according to the new, shuffled row and column
indices.

The following pseudocode is followed for generating an int array storing the
new, shuffled indices of a row/column:

- Generate a random permutation of positions three objects (0, 1, 2) can be
  arranged in using `get_rand_orientation` and passing in an int array of length
  3, each int storing the respective object's position.
- Iterate over every int element in generated array:
    - Again call `get_rand_orientation` to generate a new array of randomized
      positions.
    - Iterate over every int element in generated array:
        - Set the new position of the row/column to `outer_arr[outer_iterator] *
          3 + inner_arr[inner_iterator]`.

Repeat the above psuedocode twice to obtain two int arrays containing shuffled
indices as desired. Then, re-orient the actual puzzle according the new
positions of rows and columns using the following pseudocode:

- Copy puzzle to a temporary puzzle 2d array using `copy_puzzle`.
- Iterate over every number in the puzzle:
    - Set the value of each number in the original puzzle according to the new
      positions for each row and col using the copied puzzle.

### `remove_nums`

Prototype: `static void remove_nums(int puzzle[9][9])`

Takes in a solved (filled) puzzle and removes at least 40 random numbers so
that there is still only one solution to the puzzle.

After removing at least 40 nums, if it fails to remove a num three times
continuously, it stops and returns.

Caller provides a valid pointer to an int[9][9] containing the puzzle, that
will be edited directly by replacing nums with zeros.

Caller is responsible for seeding rand before calling the function.

- Initial setup:
    - initialize an `int removed_count` to 0 to keep track of number of removed
      items.
    - `int num_failed_tries = 0` to keep track of number of continuously failed
      tries.
- Iterate while the `removed_count <= 65` as 16 is the smallest number of clues
  a sudoku puzzle can have while still having a unique solution.
    - Generate a random row and column index using `rand() % 9` until we find a
      non-empty spot in the puzzle.
    - Temporarily set the value of the number at [row, col] to 0, and store the
      original value in a temp int.
    - Call `unique_solver` with puzzle as an argument and NULL as the second
      argument to obtain then number of solutions returned by it.
    - If the return value is == 1, indicating that the puzzle has a unique
      solution, keep the change in the puzzle, increment `removed_count` and
      reset `num_failed_tries` to 0.
    - Else, the puzzle has no solutions or multiple solutions, thus the change
      must be reverted by setting `puzzle[row][col]` to `temp`.
      `num_failed_tries` is incremented, and if `num_failed_tries == 3 &&
      removed_count >= 40`, break the loop and return.

### `get_rand_orientation`

Prototype: `static void get_rand_orientation(int arr[3])`

Generates a random permutation of positions three objects (0, 1, 2) can be
arranged in. There are six possibilities: {0, 1, 2}, {0, 2, 1}, {1, 0, 2},
{1, 2, 0}, {2, 0, 1}, {2, 1, 0}. The results are stored in the given int array
of length 3.

- Iterate over each of the three int elements in the array using a for loop:
    - Set the element value to a randomly generated int greater equal to 0 and
      less than 3 obtained by `rand() % 3`.
    - Iterate over the previous elements in the array using a for loop:
        - If any of the previous elements match the newly generated int, repeat
          outer loop for the same iterator value by decrementing the iterator
          value by 1 in the inner loop.
        - Else, continue.

### `copy_puzzle`

Prototype: `static void copy_puzzle(int og[9][9], int copy[9][9])`

Copies the given puzzle `int[9][9]` to the second given `int[9][9]`.

Caller provides valid pointers to the original and copy arrays.

- Iterate over every element in the puzzle 2d array using a for loop, and set
  the copy 2d array's value to it.

## Solver

## Common

