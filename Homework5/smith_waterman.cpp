# include "smith_waterman.h"
// Function to convert string to Radix notation
double *convert_to_radix(char* sequence) {

  double A = 0;
  double C = 1;
  double G = 2;
  double T = 3;
  double cipher = 0;
  double square = 0;

  int buffer_size = 100;
  int first_half_index = 0;
  int second_half_index = 1;
  int half_of_string = 18;
  int current_power = 49;
  int max_radix_size = 36;

  double* radix;
  char* example = new char[buffer_size];

  example = sequence;
  radix = new double[2];

  // Converts to RADIX notation
  for(int i =0; i < max_radix_size; i++) {
    // Sets the power of current radix alphabet (max of 4 ^ n-1)
    square = pow(4,(current_power));

    // If i is half, reset the cipher
    if(i == half_of_string) {
      radix[first_half_index] = cipher;
      cipher = 0;
    }

    // Determines which letter it is and uses that value to convert to Radix
    switch(example[i]) {
      case 'A' :
        cipher = cipher + (A*square);
        current_power--;
        break;
      case 'C' :
        cipher = cipher + (C*square);
        current_power--;
        break;
      case 'T' :
        cipher = cipher + (T*square);
        current_power--;
        break;
      case 'G' :
        cipher = cipher + (G*square);
        current_power--;
        break;
     }

  }
  // Set the second half of the string cipher
  radix[second_half_index] = cipher;

  return radix;
}

// Function to convert from Radix to a String
char *convert_to_str(double *radix_num) {

  double current_number;
  double power_of_four;
  double num_to_subtract;
  double first_half = radix_num[0];
  double second_half = radix_num[1];

  int first_half_index = 25;
  int current_power = 49;
  int max_radix_size = 50;

  char* example;
  example = new char[max_radix_size];
  current_number = first_half;

  // Loop through the string length and convert to radix nums to strings
  for(int i =0; i < max_radix_size; i++) {

    // If i is equal to half of the string, reset the number to the other half
    if(i == first_half_index) {
      current_number = second_half;
    }
    // Sets the power of current radix alphabet (max of 4 ^ 2)
    power_of_four = pow(4,current_power);

    num_to_subtract = current_number / power_of_four;
    num_to_subtract = int(num_to_subtract);

    // If whole number is 0 set the string letter to A
    if(num_to_subtract == 0) {
      example[i] = 'A';
      current_power--;
    }

    // If whole number is 1 set the string letter to C
    else if(num_to_subtract == 1) {
      example[i] = 'C';
      current_number = current_number - power_of_four;
      current_power--;
    }

    // If whole number is 2 set the string letter to G
    else if(num_to_subtract == 2) {
      example[i] = 'G';
      current_number = current_number - (num_to_subtract * power_of_four);
      current_power--;
    }

    // If whole number is 3 set the string letter to T
    else if(num_to_subtract == 3) {
      example[i] = 'T';
      current_number = current_number - (num_to_subtract * power_of_four);
      current_power--;
    }

    else {
      std::cout << "Didn't match anything" << std::endl;
    }
  }

  return example;

}

struct Node {
  double* radix_num;
  Node *next;
};

struct returnInfo smith_water(int match_val, int mismatch_val, int gap_val, char* sequence_one, char *sequence_two, int s_o_size, int s_t_size) {


  int** smith_matrix = new int*[s_o_size+1];
  char** moves = new char*[s_o_size+1];

  int match = match_val;
  int mismatch = mismatch_val;
  int gap = gap_val;
  int score[4] = {0, 0, 0, 0};
  int max = 0;
  int move_tracker = 0;
  int max_index[2] = {0, 0};
  int length_one = s_o_size;
  int length_two = s_t_size;
  int maxx = 0;
  int init_string;
  int least_index;
  int current_index = 0;

  if(s_o_size > s_t_size) {
    init_string = s_o_size;
    least_index = s_t_size;
  }

  else {
    least_index = s_o_size;
    init_string = s_t_size;
  }

  char* best_string = new char[least_index];
  char* actual_string = new char[least_index];

  struct returnInfo returnNode;

  // Set return node values
  returnNode.length_one = length_one;
  returnNode.length_two = length_two;
  returnNode.least_index = least_index;
  returnNode.best_string = best_string;
  returnNode.actual_string = actual_string;
  returnNode.sequence_one = sequence_one;
  returnNode.sequence_two = sequence_two;

  // Intialize matricies
  for(int i=0; i <= s_o_size; i++) {
      smith_matrix[i] = new int[s_t_size];
      moves[i] = new char[s_t_size];
    }

  // Loop through smith_matrix
  for(int k=0; k <= s_o_size; k++) {
    for(int i=0; i <= s_t_size; i++) {
      if(k == 0) {
        // Intialize row zero values
        if(i == 0) {
          smith_matrix[k][i] = 0;
          moves[k][i] = '$';
        }
        else {
          smith_matrix[k][i] = smith_matrix[k][i-1] + gap;
          moves[k][i] = '$';

        }
      }

      // Intialize column zero values
      else if(i == 0) {
        if(k == 0) {
          smith_matrix[k][i] = 0;
          moves[k][i] = '$';

        }
        else {
          smith_matrix[k][i] = smith_matrix[k-1][i] + gap;
          moves[k][i] = '$';

        }
      }

      else {
        smith_matrix[k][i] = 0;
        moves[k][i] = '$';


        // Use sequence_one letter for gap
        score[0] = smith_matrix[k][i - 1] + gap;

        // Check if they match / mismatch
        if(sequence_one[k - 1] == sequence_two[i - 1]) {
          score[1] = smith_matrix[k - 1][i - 1] + match;
        }
        else {
          score[1] = smith_matrix[k - 1][i - 1] + mismatch;
        }

        // Use sequence_two letter for gap
        score[2] = smith_matrix[k - 1][i] + gap;

        // If options are all bad, use zero and reset
        score[3] = 0;
        move_tracker = -1;

        // Print Move Matrix
        // for(int i =0; i < 4; i++) {
        //   if(score[i] > max) {
        //     max = score[i];
        //   }
        // }
        max =  *std::max_element(score, score+4);
        smith_matrix[k][i] = max;


        // Print Move Matrix
        for(int i =0; i < 3; i++) {
          if(score[i] == max) {
            move_tracker = i;
          }
        }

        // Track what moves are what
        moves[k][i] = '$';
        if(move_tracker == 0) {
          moves[k][i] = '$';
        }

        else if(move_tracker == 1) {
          moves[k][i] = 'D';

        }

        else if(move_tracker == 2) {
          moves[k][i] = 'U';

        }

        else if(move_tracker == 3) {
          moves[k][i] = 'L';
        }

      }
    }
  }

  // --------- THIS PRINTS OUT THE MATRICIES OF SCORE/MOVES ---------
  // ********
  // ********
  // ********
  // ********

  // std::cout << "------ Score Matrix ------" << std::endl;
  // for(int i = 0; i <= length_one; i++) {
  //   for(int j = 0; j <= length_two; j++) {
  //     std::cout << "  " << smith_matrix[i][j];
  //   }
  //   std::cout << std::endl;
  //
  // }
  // std::cout << "------ Score Matrix ------\n\n" << std::endl;
  //
  // // Print our moves matrix
  // std::cout << "------ Moves Matrix ------" << std::endl;
  // for(int i = 0; i <= length_one; i++) {
  //   for(int j = 0; j <= length_two; j++) {
  //     std::cout << " " << moves[i][j];
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << "------ Moves Matrix ------\n\n" << std::endl;


  // Get max indicies for matrix
  for(int i = 0; i <= length_one; i++) {
    for(int j = 0; j <= length_two; j++) {
      if(smith_matrix[i][j] > maxx) {
        maxx = smith_matrix[i][j];
        max_index[0] = i;
        max_index[1] = j;
      }
    }

  }

  returnNode.max_score = maxx;
  current_index = 0;

  int i = max_index[0];
  int j = max_index[1];

  while(moves[i][j] != '$') {
      if(moves[i][j] == 'D') {
        if(sequence_one[j - 1] == sequence_two[i - 1]) {
          best_string[current_index] = '|';
          current_index++;
        }
        else {
          best_string[current_index] = 'x';
          current_index++;
        }
        i--;
        j--;
      }

      else if(moves[i][j] == 'U') {
        best_string[current_index] = ' ';
        current_index++;
        j--;
      }

      else if(moves[i][j] == 'L') {
        best_string[current_index] = ' ';
        current_index++;
        i--;
      }

    }

  // Converts match/mismatch to best fit string
  for(int i =0; i < least_index; i++) {
    if(best_string[i] == ' ') {
      actual_string[i] = '_';
    }

    else if(best_string[i] == 'x' || best_string[i] == '|') {
      actual_string[i] = sequence_two[i];
    }
  }

  return returnNode;

}

char* random_sequence(int size) {
  int i = 0;
  int rand_num;
  char* rand_seq = new char[size];
  char* letters = "ACTG";
  while(i < size) {
    rand_num = std::rand() % 4;
    rand_seq[i] = letters[rand_num];
    i++;
  }

  return rand_seq;

}

void oneA_results(int match, int mismatch, int gap, char* denv_file, char* reads) {
  char* read_file = denv_file;
  char* viral_file = reads;
  char** sequence_array = new char*[100];
  char* giant_genome = new char[15500];
  char* row_data;
  char singleCharacter;
  int num_of_reads = 0;
  // Files to read from
  std::ifstream readfile(read_file);
  std::ifstream viralfile(viral_file);

  for(int i=0; i < 50; i++) {
    sequence_array[i] = new char[100];
  }

   //Get a character from the input file
   //singleCharacter = viralfile.get(singleCharacter);
   row_data = new char[100];
   int num_chars = 0;
   // Read in every row till the end of the file
   while(!viralfile.eof()) {
     viralfile.getline(row_data, 100);

     // If not a header file, read it in.
     if(row_data[0] != '>') {
       for(int j=0; j < 100; j++) {
         if(row_data[j] == 'A' || row_data[j] == 'C' || row_data[j] == 'T' || row_data[j] == 'G') {
           giant_genome[num_chars] = row_data[j];
           num_chars++;
         }
       }
      }
   }

   // Read in every row till the end of the file
   while(!readfile.eof()) {
     readfile.getline(row_data, 100);

     // If not a header file, read it in.
     if(row_data[0] != '>') {
       for(int j=0; j < 50; j++) {
         sequence_array[num_of_reads][j] = row_data[j];
       }
       num_of_reads++;
       }

   }

   for(int i=0; i < 30; i++) {
     struct returnInfo returnNode;
     returnNode = smith_water(match, mismatch, gap, giant_genome, sequence_array[i], 15500, 50);
     std::cout << giant_genome << std::endl;

     std::cout << "Best Score:   " << returnNode.max_score << std::endl;
     std::cout << "Sequence One: " << returnNode.sequence_one << std::endl;
     std::cout << "Alignment:    " << returnNode.best_string << std::endl;
     std::cout << "Sequence Two: " << returnNode.sequence_two << std::endl;
     std::cout << "Best String:  " << returnNode.actual_string << std::endl;
     std::cout << "Sequence: " << i << std::endl;
   }
}

void oneB_results(int match, int mismatch, int gap, int num_sequences, char* denv_file) {
  char* viral_file = denv_file;
  time_t before, after;
  char* giant_genome = new char[15500];
  char* row_data;
  char* random_seq;

  // Files to read from
  std::ifstream viralfile(viral_file);

   //Get a character from the input file
   //singleCharacter = viralfile.get(singleCharacter);
   row_data = new char[100];
   int num_chars = 0;
   // Read in every row till the end of the file
   while(!viralfile.eof()) {
     viralfile.getline(row_data, 100);

     // If not a header file, read it in.
     if(row_data[0] != '>') {
       for(int j=0; j < 100; j++) {
         if(row_data[j] == 'A' || row_data[j] == 'C' || row_data[j] == 'T' || row_data[j] == 'G') {
           giant_genome[num_chars] = row_data[j];
           num_chars++;
         }
       }
      }
   }
   time(&before);
   for(int i=0; i < num_sequences; i++) {
     struct returnInfo returnNode;
     random_seq = random_sequence(50);
     returnNode = smith_water(match, mismatch, gap, giant_genome, random_seq, 15500, 50);
     // std::cout << giant_genome << std::endl;

     std::cout << "Best Score:   " << returnNode.max_score << std::endl;
     std::cout << "Sequence One: " << returnNode.sequence_one << std::endl;
     std::cout << "Alignment:    " << returnNode.best_string << std::endl;
     std::cout << "Sequence Two: " << returnNode.sequence_two << std::endl;
     std::cout << "Best String:  " << returnNode.actual_string << std::endl;
     std::cout << "Sequence: " << i << std::endl;
   }
   time(&after);
   std::cout << "\nTime it took to search " << num_sequences << " random sequences: " << difftime(after, before) << " seconds" << std::endl;

}

void seed_based_waterman(int seed_size, char* filename) {
  char* viral_file = filename;
  time_t before, after;
  char* giant_genome = new char[15500];
  char* row_data;
  char* random_seq;
  char** sequences;
  double *radix_num = 0;

  // Files to read from
  std::ifstream viralfile(viral_file);

   //Get a character from the input file
   //singleCharacter = viralfile.get(singleCharacter);
   row_data = new char[100];
   int num_chars = 0;
   // Read in every row till the end of the file
   while(!viralfile.eof()) {
     viralfile.getline(row_data, 100);

     // If not a header file, read it in.
     if(row_data[0] != '>') {
       for(int j=0; j < 100; j++) {
         if(row_data[j] == 'A' || row_data[j] == 'C' || row_data[j] == 'T' || row_data[j] == 'G') {
           giant_genome[num_chars] = row_data[j];
           num_chars++;
         }
       }
      }
   }

   struct Node **hash_table = new Node*[num_chars];
   struct Node *current = new Node();

   for(int i = 0; i < num_chars; i++) {
     struct Node *new_node = new Node();
     new_node->next = NULL;
     new_node->radix_num = 0;
     hash_table[i] = new Node;
   }

   for(int i=0; i < num_chars - seed_size; i++) {
     char* new_sequence = new char[seed_size + 5];
     for(int j=0; j < seed_size; j++) {
       new_sequence[j] = giant_genome[i + j];
     }
     radix_num = convert_to_radix(new_sequence);
     std::cout << radix_num[0] << '\n';

     hash_table[i]->radix_num = radix_num;
   }

}

int main(int argc, char** argv) {

// seed_based_waterman(11, "viral.txt");

if(strcmp(argv[1], "--1A") == 0) {
  int match = atoi(argv[2]);
  int mismatch = atoi(argv[3]);
  int gap = atoi(argv[4]);
  char* denv_file = argv[5];
  char* reads = argv[6];
  oneA_results(match, mismatch, gap, denv_file, reads);
}

else if(strcmp(argv[1], "--1B") == 0) {
  int match = atoi(argv[2]);
  int mismatch = atoi(argv[3]);
  int gap = atoi(argv[4]);
  int size = atoi(argv[5]);
  char* denv_file = argv[6];
  oneB_results(match, mismatch, gap, size, denv_file);
}

else {
  std::cout << "Please input a proper problem number" << '\n';
}






}
