To run this code, you must first have g++ installed.
Then you run the command 'make' which will use the Makefile to compile.

For part 1, you only need to give it one filepath as it only reads in one
And works in that dataset.

For part 2, you need to give it two filepaths one to search in and the second
One to make the fragments to search for.

To run each of the homework questions:

Example: ./FASTAreadset_LL filepath --homework_problem_part second_filepath

-- PART 1A --
1A: ./FASTAreadset_LL hw_dataset.fa --A

-- PART 1B --
1B: ./FASTAreadset_LL hw_dataset.fa --B

-- PART 1C --
1C: ./FASTAreadset_LL hw_dataset.fa --C

-- PART 1D --
1D: ./FASTAreadset_LL hw_dataset.fa --D

-- PART 2A --
2A: ./FASTAreadset_LL hw_dataset.fa --2A test_genome.fasta

-- PART 2B FULL --
** This will run for all 50mers found in dataset test_genome.fasta **
2B: ./FASTAreadset_LL hw_dataset.fa --2B test_genome.fasta

-- PART 2B SUBSET --
** This will X times where X is the number at the end of the command **
2BS: ./FASTAreadset_LL hw_dataset.fa --2BS test_genome.fasta 1000
