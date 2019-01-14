# include <iostream>
# include <stdlib.h>
# include <unistd.h>
# include <fstream>
# include <cstring>
# include <time.h>
# include <cmath>
# include <algorithm>


struct returnInfo {
      int max_score;
      int least_index;
      int length_one;
      int length_two;
      char* best_string ;
      char* actual_string;
      char* sequence_one;
      char* sequence_two;
};

struct returnInfo smith_water(int match_val, int mismatch_val, int gap, char* sequence_one, char *sequence_two, int s_o_size, int s_t_size);
void oneA_results(int match, int mismatch, int gap, char* denv_file, char* reads);
char* random_sequence(int size);
