# include "FASTAreadset_LL.h"

// Function to convert string to Radix notation
double *FASTAreadset_LL::convert_to_radix(char* sequence) {

  double A = 0;
  double C = 1;
  double G = 2;
  double T = 3;
  double cipher = 0;
  double square = 0;

  int first_half_index = 0;
  int second_half_index = 1;
  int half_of_string = 25;
  int current_power = 49;
  int max_radix_size = 50;

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
char *FASTAreadset_LL::convert_to_str(double *radix_num) {

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

// Function to add a value to the LinkedList
void FASTAreadset_LL::addValue(double *val){

    int size_of_radix_array = 2;
    // Allocates next node in LL
    struct Node *new_row = new struct Node();
    // Sets the current node value to the one passed in

    current->row_radix = val;


    // Sets the next node to the new node made above
    current->next = new_row;

    // Sets current to the next node
    current = new_row;

}

// Generates the Radix Notation values
double *FASTAreadset_LL::generate_radix_array(char* row_data) {

  int index = 0;
  int radix_size = 3;
  int size_of_radix_array = 2;

  double *radix_conversion;
  int *radix_array;
  char *temp;

  radix_conversion = new double[size_of_radix_array];
  radix_conversion = convert_to_radix(row_data);

  return radix_conversion;
}

// Creates the Linked List
void FASTAreadset_LL::create_linkedList() {

  int size_of_radix_array = 2;
  int first_element = 0;
  double *radix_array;
  char *row_data;

  radix_array = new double[size_of_radix_array];
  std::ifstream FASTA_data(filename);

  // Read in every row till the end of the file
  while(!FASTA_data.eof()) {
    row_data = new char[buffer_size];

    if(!FASTA_data.getline(row_data, buffer_size)) {
      break;
    }

    // If not a header file, read it in.
    else if(row_data[first_element] != '>') {

      radix_array = generate_radix_array(row_data);

      // Adds a node to the Linked List
      FASTAreadset_LL::addValue(radix_array);

      current->next = NULL;

      }
  }
}


void *FASTAreadset_LL::fragment_search(char* fragment, FASTAreadset_LL *sequence_linked_list) {
  // Resets the radix array
  double *radix_array;
  char* radix_search_fragment;
  int radix_conversion;
  int max_row_size = 50;
  int size_of_radix_array = 2;

  radix_search_fragment = new char[max_row_size];
  radix_array = new double[size_of_radix_array];

  radix_search_fragment = fragment;

  radix_array = generate_radix_array(radix_search_fragment);

  sequence_linked_list->current = sequence_linked_list->head;

  while(sequence_linked_list->current->next != NULL) {

    if(radix_array[0] == sequence_linked_list->current->row_radix[0] &&
       radix_array[1] == sequence_linked_list->current->row_radix[1]) {
         std::cout << "*** Match ***: ";
         sequence_linked_list->num_of_50mer++;
         return &sequence_linked_list->current;
       }

    sequence_linked_list->current = sequence_linked_list->current->next;
  }
  std::cout << "--- No Match ---: ";
  return &sequence_linked_list->current->next;
}

// Creates the Linked List
void FASTAreadset_LL::create50mer_linkedList() {

  int size_of_radix_array = 2;
  int first_element = 0;
  int index = 0;
  int start_index = 0;
  int max_row_size = 50;
  int current_char_reads = 0;
  int max_char_reads = 50;
  char single_character;
  double *radix_array;
  char *row_data;

  radix_array = new double[size_of_radix_array];
  std::ifstream staff_data(bac_ant_file);
  row_data = new char[max_row_size];

  while (!staff_data.eof()) {          // loop getting single characters
  // Read in every row till the end of the file

    staff_data.get(single_character);

    if(index == max_row_size) {
      radix_array = generate_radix_array(row_data);

      // Adds a node to the Linked List
      FASTAreadset_LL::addValue(radix_array);

      current->next = NULL;

      // Frees memory for the row array
      start_index++;

      staff_data.seekg(start_index, staff_data.beg);

      index = 0;
    }

    // Read till new line Character
    else if(single_character == '\n') {
      staff_data.get(single_character);
      row_data[index] = single_character;
      index++;
    }

    // Check if it's the end of the file
    else if(staff_data.eof()) {
      break;
    }

    // If not a header file, read it in.
    else if(index < max_row_size) {
      row_data[index] = single_character;
      index++;
    }


  }
}

int main(int argc, char *argv[]) {


  if(strcmp(argv[2], "--A") == 0) {
    char *seq;
    int i = 0;
    FASTAreadset_LL *sequence_LL;
    sequence_LL = new FASTAreadset_LL(argv[1]);

    // FASTAreadset_LL *sequence_LL2 = sequence_LL;

    // Sets class values
    sequence_LL->max_radix_row = 50;

    // The file that is used to created the Linked List

    sequence_LL->create_linkedList();

    sequence_LL->current = sequence_LL->head;

    // Iterate over all nodes
    while(sequence_LL->current->next != NULL) {
      sequence_LL->current = sequence_LL->current->next;
      i++;
    }

    std::cout << "Number of Sequences: " << i-1 << std::endl;

  }

  else if(strcmp(argv[2], "--B") == 0) {
    char *seq;
    time_t before_destruction, after_destruction;


    FASTAreadset_LL *sequence_LL;
    sequence_LL = new FASTAreadset_LL(argv[1]);


    // Sets class values
    sequence_LL->max_radix_row = 50;

    // The file that is used to created the Linked List

    sequence_LL->create_linkedList();

    // Destructor
    time(&before_destruction);
    delete sequence_LL;
    time(&after_destruction);
    std::cout << "Time it took to deallocate: " << difftime(after_destruction, before_destruction) << " seconds" << std::endl;

  }

  else if(strcmp(argv[2], "--C") == 0) {
    char *seq;
    time_t before_copy, after_copy;


    FASTAreadset_LL *sequence_LL;
    sequence_LL = new FASTAreadset_LL(argv[1]);


    // Sets class values
    sequence_LL->max_radix_row = 50;

    // The file that is used to created the Linked List

    sequence_LL->create_linkedList();

    // Destructor
    time(&before_copy);
    FASTAreadset_LL *sequence_LL2 = sequence_LL;
    time(&after_copy);
    std::cout << "Time it took to call the copy constructor: " << difftime(after_copy, before_copy) << " seconds" << std::endl;

  }

  else if(strcmp(argv[2], "--D") == 0) {
    char *seq;

    // Sequences defined in the homework description
    char* sequence_one = "CTAGGTACATCCACACACAGCAGCGCATTATGTATTTATTGGATTTATTT";
    char* sequence_two = "GCGCGATCAGCTTCGCGCGCACCGCGAGCGCCGATTGCACGAAATGGCGC";
    char* sequence_three = "CGATGATCAGGGGCGTTGCGTAATAGAAACTGCGAAGCCGCTCTATCGCC";
    char* sequence_four = "CGTTGGGAGTGCTTGGTTTAGCGCAAATGAGTTTTCGAGGCTATCAAAAA";
    char* sequence_five = "ACTGTAGAAGAAAAAAGTGAGGCTGCTCTTTTACAAGAAAAAGTNNNNNN";

    FASTAreadset_LL *sequence_LL;
    sequence_LL = new FASTAreadset_LL(argv[1]);

    // Sets class values
    sequence_LL->max_radix_row = 50;

    // The file that is used to created the Linked List

    sequence_LL->create_linkedList();

    std::cout << "-----Fragement Search Results------" << std::endl;
    std::cout << "" << std::endl;

    // Displays *** MATCH *** if one was found, otherwise displays --- No Match ---
    // While still just returning the address to the pointer of either
    std::cout << "Results for Sequence 1: " << sequence_LL->fragment_search(sequence_one, sequence_LL) << std::endl;
    std::cout << "Results for Sequence 2: " << sequence_LL->fragment_search(sequence_two, sequence_LL) << std::endl;
    std::cout << "Results for Sequence 3: " << sequence_LL->fragment_search(sequence_three, sequence_LL) << std::endl;
    std::cout << "Results for Sequence 4: " << sequence_LL->fragment_search(sequence_four, sequence_LL) << std::endl;
    std::cout << "Results for Sequence 5: " << sequence_LL->fragment_search(sequence_five, sequence_LL) << std::endl;
  }

  else if(strcmp(argv[2], "--2A") == 0) {
    FASTAreadset_LL *sequence_LL;
    FASTAreadset_LL *staff_LL;

    sequence_LL = new FASTAreadset_LL(argv[1]);
    staff_LL = new FASTAreadset_LL();
    staff_LL->bac_ant_file = argv[3];

    int i = 0;
    // Sets class values
    sequence_LL->max_radix_row = 50;
    staff_LL->max_radix_row = 50;


    // The file that is used to created the Linked List

    // sequence_LL->create_linkedList();

    staff_LL->create50mer_linkedList();

    staff_LL->current = staff_LL->head;

    // Iterate over all nodes
    while(staff_LL->current->next != NULL) {
      staff_LL->current = staff_LL->current->next;
      i++;
    }

    std::cout << "\nNumber of 50 Character Fragments: " << i << std::endl;
  }

  else if(strcmp(argv[2], "--2B") == 0) {
    time_t before_copy, after_copy;
    int max_number_of_searches = 100;

    // Intialize two classes
    FASTAreadset_LL *sequence_LL;
    FASTAreadset_LL *staff_LL;

    // Allocate memory for them
    // Sequence takes in the file as part of a constructor
    // Staff just uses the argument to set the variable
    sequence_LL = new FASTAreadset_LL(argv[1]);
    staff_LL = new FASTAreadset_LL();
    staff_LL->bac_ant_file = argv[3];

    int i = 0;
    // Sets class values
    sequence_LL->max_radix_row = 50;
    staff_LL->max_radix_row = 50;

    // Creates both linked lists
    sequence_LL->create_linkedList();
    staff_LL->create50mer_linkedList();

    // Sets Current
    staff_LL->current = staff_LL->head;

    // Iterate over all nodes
    time(&before_copy);
    while(staff_LL->current->next != NULL) {
      std::cout << "Results for Sequence: "
                // Calls each 50mer fragment inside of the staff_LL linked lists
                // And displays the result of the search
                << sequence_LL->fragment_search(staff_LL->convert_to_str(staff_LL->current->row_radix), sequence_LL)
                << std::endl;
      staff_LL->current = staff_LL->current->next;
      i++;
    }
    time(&after_copy);

    // Output Results
    std::cout << "\nTime it took to search all 50mers: " << difftime(after_copy, before_copy) << " seconds" << std::endl;
    std::cout << "Number of 50 Character Fragments: " << i << std::endl;
  }

  else if(strcmp(argv[2], "--2BS") == 0) {
    time_t before_copy, after_copy;
    int max_number_of_searches = atoi(argv[4]);
    int current_number_of_searches = 0;

    // Intialize two classes
    FASTAreadset_LL *sequence_LL;
    FASTAreadset_LL *staff_LL;

    // Allocate memory for them
    // Sequence takes in the file as part of a constructor
    // Staff just uses the argument to set the variable
    sequence_LL = new FASTAreadset_LL(argv[1]);
    staff_LL = new FASTAreadset_LL();
    staff_LL->bac_ant_file = argv[3];

    int i = 0;
    // Sets class values
    sequence_LL->max_radix_row = 50;
    staff_LL->max_radix_row = 50;
    staff_LL->num_of_50mer = 0;

    // Creates both linked lists
    sequence_LL->create_linkedList();
    staff_LL->create50mer_linkedList();

    // Sets Current
    staff_LL->current = staff_LL->head;

    // Iterate over all nodes
    time(&before_copy);
    while(current_number_of_searches < max_number_of_searches) {
      std::cout << "Results for Sequence: "
                // Calls each 50mer fragment inside of the staff_LL linked lists
                // And displays the result of the search
                << sequence_LL->fragment_search(staff_LL->convert_to_str(staff_LL->current->row_radix), sequence_LL)
                << std::endl;
      staff_LL->current = staff_LL->current->next;
      i++;

      current_number_of_searches++;
    }
    time(&after_copy);

    // Output Results
    std::cout << "\nTime it took to search all 50mers: " << difftime(after_copy, before_copy) << " seconds" << std::endl;
    std::cout << "Number of 50 Character Fragments: " << sequence_LL->num_of_50mer << std::endl;
  }
}
