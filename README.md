# Dartmouth CS50 20S, Sudoku Project

Members: Pratinav Bagla, Wendell Wu, Eyasu Lemma

## Usage

`make` to compile.

`./sudoku [create|solve]`

To enable/disable DEBUG prints, uncomment/comment the DEBUG variable in the each module's respective Makefile.

Please note: piping sudoku create to sudoku solve will not work with debug statements enabled from creator module. Please disable debug flag in the creator module makefile AND sudoku module makefile by commenting it out before attempting to pipe.

## Collaborating

Details on how to collaborate are defined in `COLLABORATING.md`.

Also see `STYLEGUIDE.md` and `TODO.md`.

## Project Structure

- README.md
- REQUIREMENTS.md
- DESIGN.md
- IMPLEMENTATION.md
- TESTING.md
- COLLABORATING.md
- STYLEGUIDE.md
- TODO.md
- Makefile
- Testing scripts: testing.sh, regress.sh
- creator/
- solver/
- common/
- sudoku.c
- ...

