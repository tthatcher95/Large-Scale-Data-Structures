# include <iostream>
# include <stdlib.h>
# include <unistd.h>
# include <fstream>
# include <cstring>
# include <time.h>
# include <cmath>

class FASTAreadset_LL {

  struct Node {
        double *row_radix;
        struct Node *next;
    };

public:
    int buffer_size;
    int max_radix_row;
    int num_of_50mer;
    char* filename;
    char* bac_ant_file;
    struct Node *head;
    struct Node *current;

    // Function declarations
    double *convert_to_radix(char* sequence);

    char* convert_to_str(double *radix_num);

    // These two build the linked list
    void addValue(double *val);

    double *generate_radix_array(char* some_row_data);

    void create_linkedList();

    void create50mer_linkedList();

    void *fragment_search(char* fragment, FASTAreadset_LL *sequence_linked_list);

    // Constructor
    FASTAreadset_LL() {
        head = new struct Node();
        current = new struct Node();
        head = current;
    }

    // Takes in a filepath and uses that
    // For the FASTA file
    FASTAreadset_LL(char *filepath) {

      head = new struct Node();
      current = new struct Node();
      head = current;

      buffer_size = 500;

      filename = new char[buffer_size];
      filename = filepath;

      std::cout << "The file is set to: " << filename << std::endl;
    }

    // Copy constructor
    FASTAreadset_LL(const FASTAreadset_LL &LL2) {
      current = LL2.current;
      head = LL2.head;
     }



    ~FASTAreadset_LL() {
      // Deletes all nodes in linked list
      while(head->next != NULL) {
        current = head->next;
        delete head;
        head = current;
      }

    }


};
