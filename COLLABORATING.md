# Collaborating

Project status, TODOs, and responsibilities are in `TODO.md`.

For code, please follow the style guide defined in `STYLEGUIDE.md`.

## Git

We will use git to manage our project. [This][1] is a great resource for
understanding git's underlying model. We will use some sort of branching
strategy/model that has not yet been solidified. Each commit should ideally
address a specific change and the commit message should be clear, concise, and
informative (should also include the names of the files/modules addressed). For
example, `creator.c: fix segmentation fault in main`. Commit messages are also
generally written in the imperative.

Note: please remember to `git pull` before starting work and `git push` after
you are done. In case of conflicts, *please contact the rest of the team!.*

## Data Files

If generating files for tests etc. please store them in a directory prefixed
with `data`. For example `data-tests-1`, `data-random`, `data3` etc. This will
be ignored by git as per the `.gitignore` and prevent it from being tracked and
uploaded to the remote.

[1]: https://missing.csail.mit.edu/2020/version-control/

