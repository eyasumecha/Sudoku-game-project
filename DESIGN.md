# Design

5/25/20: Pratinav Bagla, Eyasu Lemma, Wendell Wu 

## User interface

Command line:
```
sudoku [create|solve]
```

## Inputs and Outputs

### Inputs

- Create mode: command line argument.
- Solve mode: command line argument,  puzzle from `stdin`.

### Outputs

- Create mode: new puzzle to `stdout`.
- Solve mode: solved puzzle to `stdout`.

## Functional decomposition into modules

- Creator
- Solver

## Functional Decomposition into Modules
 
1. Main - validate arguments and call appropriate module (wendell)
2. Solver Module - (eyasu, pratinav)
    -  *solver* - Function which returns true or false depending on if there is one or multiple/no solutions, takes a pointer to the 2d array, and directly edits the items inside(eyasu) (pratinav)
3. Creator Module - (wendell)
    - *creator* - function which creates the 2d unsolved puzzle and uses *puzzlePrinter* to print the puzzle to stdout
4. Common
    - *puzzleLoader* - take a puzzle (solved or unsolved) in from stdin and put it into a 2D array. (0’s represent missing nums) (Eyasu)
    - *puzzlePrinter* take a 2D array and print the puzzle stored inside (wendell)
    - *RNG1Thru9* - generate a random number between 1 and 9 (pratinav)
    - *wipeBoard* - in case creator doesn’t create a unique solution, wipe the board and try again(wendell)
    - *boardCopy* - make a copy of the current board(wendell)
    - *rowCheck* Given a row num, int, and 2D array, check if the number is already on that row. (eyasu)
    - *colCheck* Given a col num, int, and 2D array, check if the number is already on that col. (pratinav)
    - *gridCheck* Given a grid region (1-9 labeled like below), int, and 27x27 2D array, check if the number is already within its 3x3 grid.(wendell)
        - 1 | 2 | 3
        - 4 | 5 | 6
        - 7 | 8 | 9
        - 
        - EACH OF THE ABOVE NUMS IS A 3x3 REGION, NOT A NUMBER ITSELF

The grid is organized into the 2D array like so

Each row is a pointer to an array

Each column is the array itself.

![Diagram]()

## Pseudocode for logic/algorithm flow

1. Solver
    - For each cell
    - If it is a 0
        - Place it on the stack to backtrace
        - For each num 1-9
            - Check the rules (grid, row, col) for the num.
            - If all 3 rules checks pass
                - Place the num in that spot
2. Creator
    - Populate a board
    - Remove 50 random nums from the board
    - Create a copy of the board and pass it to solver
    - If solver returns true, then it has a unique solution and shall be printed to stdout.

## Testing

Test invalid parameters
Test creator
Test solver using non-unique solutions
Test solver using unique solutions

