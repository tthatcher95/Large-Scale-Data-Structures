To run this code, you must first have g++ installed.
Then you run the command 'make' which will use the Makefile to compile.

This requires that the sequences be in a read-file and the denv sequence to be in
a file as well. Both of which are passed in as arguments when running this code.

To run this code it requires several parameters to be entered.

For Question 1: Part A

./smith_waterman --1A match-score mismatch-score gap-score read-file denv-file

For Question 1: Part B

./smith_waterman --1B match-score mismatch-score gap-score number-of-genomes denv-file
