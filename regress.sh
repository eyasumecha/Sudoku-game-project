#!/bin/bash

# regress.sh    Pratinav Bagla <pratinav.bagla.23@dartmouth.edu>    16 April, 2020
# Dartmouth CS50 Lab 2, Spring 2020 w/ Prof. Kommineni
#
# program for regression testing
# usage: regression.sh dirname testfilename...
# dirname is the path to the directory containing the base test results
# each testfilename is the path to a file containing the bash commands for each test case
# the program must at least be given the dirname and one testfilename argument
# the output of the program is stored in a directory named with the current timestamp
# in the format data-YYYYMMDD.HHMMSS
# if dirname does not exist, then dirname is created and the output is stored
# there instead
# if dirname exists, the program prints the difference between dirname
# and the new test directory
# exit status
#   0     no errors, and (if dirname exists) no diff between dirname and new dir
#   1     (if dirname exists) diff between dirname and new dir
#  >1    an error occured

# helper function that prints the second argument to stderr and exits with the
# code given in the first argument
function error() {
  echo "$2" >&2
  exit $1
}

# helper function that calls the error function if the last command exited
# with a code greater than zero
function on_fail() {
  if [ $? -ne 0 ]; then
    error $1 "$2"
  fi
}

# MAIN BODY

# validate arguments
if [ $# -lt 2 ]; then
  error 2 "Usage: regression.sh dirname testfilename..."
fi

if [ -e $1 ] && [ ! -d $1 ]; then
  error 3 "Error: $1 exists but is not a directory"
fi

for i in "${@:2}"; do   # slicing the args array rather than shifting
  if [ ! -f "$i" ]; then
    error 4 "Error: $i is not a regular file or does not exist"
  fi
  if [ ! -r "$i" ]; then
    error 5 "Error: $i is not readable"
  fi
done

# get current date in YYYYMMDD.HHMMSS format and create new dir
newdir=data-$(date "+%Y%m%d.%H%M%S")
on_fail 6 "Error: could not get date"
mkdir "$newdir"
on_fail 7 "Error: could not create directory $newdir"

# save original working dir
old_pwd="$(pwd)"
# iterate over and test all testfilenames
for i in "${@:2}"; do
  # since each testfilename could be in any dir, cd into the file's dir before testing
  # and cd back into the original working dir after testing 
  dir_name="$(dirname $i)"
  file_name="$(basename $i)"
  cd "$dir_name"
  cp "./$file_name" "$old_pwd/$newdir/$file_name.test"
  on_fail 8 "Error: could not copy $dir_name/$file_name to $newdir/$file_name.test"
  bash "./$file_name" < /dev/null > "$old_pwd/$newdir/$file_name.stdout" 2> "$old_pwd/$newdir/$file_name.stderr"
  echo $? > "$old_pwd/$newdir/$file_name.status"
  cd "$old_pwd"
done

if [ ! -d $1 ]; then
  mv "$newdir" "$1"
  on_fail 9 "Error: could not move results directory $newdir to $1"
  echo "saved test results in $1"
  exit 0
fi

echo "saved test results in $newdir"
echo "comparing $newdir with $1..."
diff -q "$1" "$newdir"
if [ $? -eq 0 ]; then
  echo "no differences"
  exit 0
fi
exit 1
