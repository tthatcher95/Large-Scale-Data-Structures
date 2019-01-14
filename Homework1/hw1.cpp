# include "classes.h"

int FASTAreadset::get_file_lines(char* filename, bool read_till_end) {

  std::ifstream infile(filename);

  int lines = 0;
  int custom_length = 0;
  char cur_line[columns];

  if(read_till_end == false) {
    // Read the file into a pointer
    while(custom_length < length_of_read) {

      // Reads the current line into var 'cur_line'
      infile.getline(cur_line, columns);

      // If not a header line, skip it.
      if(cur_line[0] != '>') {
        lines++;
      }

      custom_length++;
    }

    infile.close();
    return lines;

  }

  else {

    // Read the file into a pointer
    while(infile) {

      // Reads the current line into var 'cur_line'
      infile.getline(cur_line, columns);

      // If not a header line, skip it.
      if(cur_line[0] != '>') {
        lines++;
      }
    }

    return lines;
  }

  infile.close();
  return lines;
}

int convert_to_str(char* header, int start_index, int stop_index) {

  int reads = 0;
  int tmp_index = 0;
  char temp[start_index + stop_index + 500];

  for(int x = start_index + 1; x <= stop_index; x++) {
    temp[tmp_index] = header[x];
    tmp_index++;
  }

  reads = atoi(temp);

  return reads;

}
void FASTAreadset::read_header(char* current_row, int *datasets_counters) {

  int index = 0;
  int row_index = 0;
  int row_length = strlen(current_row);
  int *underscores;
  int total_reads = 0;
  int i = 0;

  underscores = new int[1000];
  while(i <= row_length + 100) {

    if(current_row[i] == '_') {
      underscores[row_index++] = i;
      i++;
    }

    else if(i == row_length) {
      underscores[row_index++] = i;
      break;
    }

    else {
      i++;
    }
  }

  for(int j = 0; j < row_index; j++) {
    datasets_counters[j] = datasets_counters[j] + convert_to_str(current_row, underscores[j], underscores[j + 1]);

  }

}

int sort_sequence(char* sequence_1, char *sequence_2) {

  for(int i = 0; i < strlen(sequence_1); i++) {
    if (sequence_1[i] < sequence_2[i]) {
      return 2;
    }

    else if(sequence_2[i] < sequence_1[i]) {
      return 1;
    }

    else if(sequence_2[i] == sequence_1[i]) {
      continue;
    }

    else {
      cout << "Error in processing string" << endl;
      return -1;
    }
  }
}

char** FASTAreadset::insertionSort(char** arr, int n, int num_sorts)
{
  int i, j;
  char *key;
  for (i = 1; i < n; i++)
  {
    key = arr[i];
    j = i-1;
    int sort = 0;

   /*
   Move elements of arr[0..i-1], that are
   greater than key, to one position ahead
   of their current position
   */
      while (j >= 0 && sort_sequence(arr[j], key) == 1 && sort < num_sorts)
      {
        arr[j+1] = arr[j];
        j = j-1;
        sort++;

      }
      arr[j+1] = key;
    }

    return arr;
  }

char** FASTAreadset::read_file_and_stats(char* filename, bool read_till_end) {

  number_of_lines = get_file_lines(filename, read_till_end);

  int row_num = 0;
  int custom_length = 0;
  int cur_char = 0;
  char row_data[1000 + columns];


  all_data = new char*[number_of_lines];
  letters = new int[4];
  datasets_counters = new int[num_datasets];

  std::ifstream infile(filename);

  for(int i=0; i < num_datasets; i++) {
    datasets_counters[i] = 0;
  }

  for(int x=0; x < 4; x++) {
    letters[x] = 0;
  }

  // --------- EXECUTES TILL EOF --------------
  // ---------    Default Mode   --------------
  while(!infile.eof()) {

    if(cur_char >= (length_of_read) && !read_till_end) {
      break;
    }
    infile.getline(row_data, columns);

    if(row_data[0] == '>') {
      read_header(row_data, datasets_counters);
    }

    // If not a header file, read it in.
    else if(row_data[0] != '>') {
      all_data[row_num] = new char[columns];

      for(int loc = 0; loc < strlen(row_data); loc++) {
        all_data[row_num][loc] = row_data[loc];
      //
        // Counts letters while reading and copying data
      switch(row_data[loc]) {
        case 'A' :
           letters[A] = letters[A] + 1;
           break;
        case 'C' :
           letters[C] = letters[C] + 1;
        case 'T' :
           letters[T] = letters[T] + 1;
           break;
        case 'G' :
           letters[G] = letters[G] + 1;
           break;
       }
     }

     row_num++;

    }

    else {
       cout << "Error Reading File" << endl;
    }
    cur_char++;

  }

  infile.close();

  return all_data;
  }

void FASTAreadset::getStats(char* filename, bool read, char problem_part) {
  int up_to;

  number_of_lines = get_file_lines(filename, read);

  switch(problem_part) {
    case 'A' :
       all_data = read_file_and_stats(filename, read);
       break;
    case 'B' :
       all_data = read_file_and_stats(filename, read);
       break;
    case 'C' :

       all_data = read_file_and_stats(filename, read);

       cout << "\n------- PART C: A -------" << endl;
       cout << "Unique Sequences: " << number_of_lines << endl;

       cout << "\n------- PART C: B -------" << endl;

       for(int i=0; i < num_datasets; i++) {
         cout << "Number of reads in dataset " << i << ":  " << datasets_counters[i] << endl;
       }

       // With the array of letters, output the total number of each letter
       cout << "\n------- PART C: C -------" << endl;

       cout << "Number of A's: " << letters[A] << endl;
       cout << "Number of T's: " << letters[C] << endl;
       cout << "Number of C's: " << letters[T] << endl;
       cout << "Number of G's: " << letters[G] << endl;
       break;
    case 'D' :
       all_data = read_file_and_stats(filename, read);
       break;

    case 'E' :
       all_data = read_file_and_stats(filename, read);
       cout << "\n-------- PART E ---------" << endl;

       char** sorted_data = insertionSort(all_data, subset_max, subset_max);

       cout << "\n -- Sorted Array -- " << endl;

       for(int i = 0; i < subset_max; i++) {
         cout << sorted_data[i] << endl;
       }
       break;
     }
  }

int main(int argc, char *argv[]) {

    // Declare an object of class geeks


    if(strcmp(argv[2], "--A") == 0) {

      FASTAreadset *part_a;
      part_a = new FASTAreadset;

      // Set Values for object
      part_a->max_filepath_size = 500;
      part_a->columns = 1000;
      part_a->A = 0;
      part_a->C = 1;
      part_a->T = 2;
      part_a->G = 3;
      part_a->num_datasets = 15;
      part_a->length_of_read = 1000000;

      // part_a->getStats("hw_dataset->fa");
      part_a->getStats(argv[1], false, 'A');

      // Calls destructor
      delete part_a;
    }

    else if(strcmp(argv[2], "--B") == 0) {

      FASTAreadset *part_b;
      part_b = new FASTAreadset;

      // Set Values for object
      part_b->max_filepath_size = 500;
      part_b->columns = 1000;
      part_b->A = 0;
      part_b->C = 1;
      part_b->T = 2;
      part_b->G = 3;
      part_b->num_datasets = 15;

      // part_b->getStats("hw_dataset->fa");
      part_b->getStats(argv[1], true, 'B');

      // Calls destructor
      delete part_b;
    }

    else if(strcmp(argv[2], "--C") == 0) {

      FASTAreadset *part_c;
      part_c = new FASTAreadset;

      // Set Values for object
      part_c->max_filepath_size = 500;
      part_c->columns = 1000;
      part_c->A = 0;
      part_c->C = 1;
      part_c->T = 2;
      part_c->G = 3;
      part_c->num_datasets = 15;

      // part_c->getStats("hw_dataset->fa");
      part_c->getStats(argv[1], true, 'C');

      // Calls destructor
      delete part_c;
    }

    else if(strcmp(argv[2], "--D") == 0) {

      FASTAreadset *part_d;
      part_d = new FASTAreadset;
      time_t before_destruction, after_destruction;

      // Set Values for object
      part_d->max_filepath_size = 500;
      part_d->columns = 1000;
      part_d->A = 0;
      part_d->C = 1;
      part_d->T = 2;
      part_d->G = 3;
      part_d->num_datasets = 15;

      // part_d->getStats("hw_dataset->fa");

      part_d->getStats(argv[1], true, 'D');

      // Calls destructor
      time(&before_destruction);
      delete part_d;
      time(&after_destruction);

      cout << "Time it took to deallocate: " << difftime(after_destruction, before_destruction) << " seconds" << endl;
    }

    else if(strcmp(argv[2], "--E") == 0) {

      FASTAreadset *part_e;
      part_e = new FASTAreadset;

      // Set Values for object
      part_e->max_filepath_size = 500;
      part_e->columns = 1000;
      part_e->A = 0;
      part_e->C = 1;
      part_e->T = 2;
      part_e->G = 3;
      part_e->num_datasets = 15;
      part_e->length_of_read = 10;
      part_e->subset_max = 10000;

      // part_e->getStats("hw_dataset->fa");
      part_e->getStats(argv[1], true, 'E');

      // Calls destructor
      delete part_e;
    }

    else {
     cout << "Invalid Arguments Passed In (Please refer to the README)" << endl;
    }

    return 0;
}
