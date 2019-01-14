# include <iostream>
# include <stdlib.h>
# include <unistd.h>
# include <fstream>
# include <cstring>
# include <time.h>
# include <cmath>

class prefix_trie {

  struct Node {
    struct Node *nextA;
    struct Node *nextC;
    struct Node *nextG;
    struct Node *nextT;
  };

  struct Stack {
    struct Node *next;
    struct Node *head;
  };

public:
  struct Stack *branch_stack;
  struct Node *root;
  struct Node *current;
  char* genome_file;
  char* best_match;
  char* random_sequence;
  int num_mismatches;
  int num_nodes;
  int length_of_file;

  void build_tree(char* sequenceTwo, int seq_len);

  void add_all_paths(struct Node *something);

  void get_length_of_file(char* filename);

  void get_random_string(int length_of_file);

  void get_random_string_error(int length_of_file, double error_percent);

  void pop();

  void push(struct Node *new_path);

  int get_all_matches();

  int search_tree(char* sequenceThree, int seq_len);

  char get_other_letter(char letter);

  double get_random_num();


  // Constructor
  prefix_trie() {
    num_mismatches = 0;
    num_nodes = 0;

    root = new struct Node();
    root->nextA = NULL;
    root->nextC = NULL;
    root->nextT = NULL;
    root->nextG = NULL;

    current = new struct Node();
    current->nextA = NULL;
    current->nextC = NULL;
    current->nextT = NULL;
    current->nextG = NULL;

    branch_stack = new struct Stack();
    branch_stack->head = NULL;
    branch_stack->next = NULL;
  }

  // Copy constructor
  prefix_trie(const prefix_trie &trie2) {
    num_mismatches = trie2.num_mismatches;
    num_nodes = trie2.num_nodes;
    branch_stack = trie2.branch_stack;
    current = trie2.current;
    branch_stack->head =  trie2.branch_stack->head;
   }

   // Destructor
  ~prefix_trie() {
    delete root;
    delete current;
    delete branch_stack;
  }
};
