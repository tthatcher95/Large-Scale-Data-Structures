# include <iostream>
# include <stdlib.h>
# include <unistd.h>
# include <fstream>
# include <cstring>
# include <time.h>
# include <cmath>

class suffix_tree {

  struct suffixNode {
    int string_start;
    int string_end;
    struct suffixNode *nextA;
    struct suffixNode *nextC;
    struct suffixNode *nextT;
    struct suffixNode *nextG;
  };

public:
  suffixNode *root;
  suffixNode *current;
  char* genome_file;
  char* random_sequence;
  int length_of_file;
  int nodes;
  int matches;

  void insert(char* giant_string);

  int search(char* sequence, int len);

  void get_length_of_file(char* filename);

  void split_node(int start, char* sequence);

  void get_random_string(int length, int mersize);


  // Constructor
  suffix_tree() {
    int max_file_size = 15000;
    genome_file = new char[max_file_size];

    root = new struct suffixNode();
    root->string_start = 0;
    root->string_end = 0;
    root->nextA = NULL;
    root->nextC = NULL;
    root->nextT = NULL;
    root->nextG = NULL;

    current = new struct suffixNode();
    current->string_start = 0;
    current->string_end = 0;
    current->nextA = NULL;
    current->nextC = NULL;
    current->nextT = NULL;
    current->nextG = NULL;
    nodes = 0;
    matches = 0;
  }

  // Copy constructor
  suffix_tree(const suffix_tree &tree) {
    nodes = tree.nodes;
    matches = tree.matches;
    current = tree.current;
    root = tree.root;
    genome_file = tree.genome_file;
   }

   // Destructor
  ~suffix_tree() {
    delete root;
    delete current;
    delete genome_file;
  }

};
