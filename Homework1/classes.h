# include <iostream>
# include <stdlib.h>
# include <unistd.h>
# include <fstream>
# include <cstring>
# include <time.h>


using namespace std;

// Declare class FASTAreadset
class FASTAreadset
{

  public:
    char *cwd;
    int *datasets_counters;
    int *letters;
    char** all_data;
    bool read_to_end;
    int length_of_read;
    int number_of_lines;
    int max_filepath_size;
    int columns;
    int A;
    int C;
    int T;
    int G;
    int num_datasets;
    int subset_max;

    // Reads in the current directory and uses that
    // For the FASTA file
    FASTAreadset() {

      max_filepath_size = 1000;
      cwd = new char[max_filepath_size];
      cwd = getcwd(cwd, max_filepath_size);

      // If a CWD is valid, use that
      if (cwd == NULL) {
       cout << "The filepath is invalid: " << cwd << endl;


      }
      // Else spit an error
      else {
        cout << "The filepath is now: " << cwd << endl;
      }

    }

    // Takes in a filepath and uses that
    // For the FASTA file
    FASTAreadset(char *filepath) {
      char* new_filepath = new char[buffer_size];
      new_filepath = filepath;
      cout << "The file is set to: " << new_filepath << endl;

    }

    int get_file_lines(char* filename, bool read);

    void read_header(char* x, int *datasets_counters);

    char** read_file_and_stats(char* filename, bool read);

    void getStats(char* filename, bool read, char current_problem);

    char** insertionSort(char** arr, int n, int subset);

    ~FASTAreadset()
      {
        // Deletes entire array of sequence data
        for(int i=0; i < number_of_lines; i++) {
          delete[] all_data[i];
        }
      }

};
