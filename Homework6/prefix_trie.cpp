#include "prefix_trie.h"

int prefix_trie::get_all_matches() {

  int matches = 0;
  int is_match = 0;

  // Iterates through the entire file array created with a step size of 1, and
  // A mer size of 36.
  for(int i = 0; i < length_of_file - 35; i++) {
    is_match = 0;
    char* current_mer = new char[40];

    // Generates a mer of size 36
    for(int j = 0; j < 36; j++) {
      current_mer[j] = genome_file[i + j];
    }

    // Searches the tree each time for the 'current_mer'
    std::cout << current_mer << '\n';
    is_match =search_tree(current_mer, 36);
    if(is_match == 1) {
      matches++;
    }

    delete best_match;
    delete current_mer;

  }

  return matches;

}

void prefix_trie::get_length_of_file(char* filename) {
  // Allocates more than enough for the file
  genome_file = new char[15000];
  int length_file = 0;

  // Character to be reading in
  char c = 'C';
  std::ifstream genome_data(filename);

  while (genome_data.get(c)) {
    if(c == 'A' || c == 'C' || c == 'T' || c == 'G') {
      genome_file[length_file++] = c;
    }
  }
  genome_data.close();
  length_of_file = length_file;
}

// String with no errors, reads from 0-36 inside the genome_file
void prefix_trie::get_random_string(int length_file) {
  int max_position = rand() % (length_file - 36);
  random_sequence = new char[50];
  int j=0;
  for(int i=max_position; i < max_position + 36; i++) {
    random_sequence[j++] = genome_file[i];
  }
}

// returns a value between 0-1
double prefix_trie::get_random_num() {
    return (double)rand() / (double)RAND_MAX ;
}

char prefix_trie::get_other_letter(char letter) {
  // Generates a number between 0-3
  int rand_num = rand() % 4;
  char* alphabet = "ACTG";

  // Sets current 'random' letter to the letter at alphabet[rand_num]
  char rand_letter = alphabet[rand_num];
  // Checks if it is the same letter, if it is, generate again, until they it
  // Is not the same
  while(rand_letter == letter) {

    rand_num = rand() % 3;
    rand_letter = alphabet[rand_num];
  }
  return alphabet[rand_num];
}
void prefix_trie::get_random_string_error(int length_file, double error_percent) {
  // Gets random value from 0 - (length_of_file - 36)
  int max_position = rand() % (length_file - 35);

  // Allocates memory for the random_sequence
  random_sequence = new char[50];
  int j=0;

  // Checks each time if a random num bewt
  for(int i=max_position; i < max_position + 36; i++) {

    // If a random num between 0-1 is less than error_percent, get another letter
    if(get_random_num() < error_percent) {
      random_sequence[j++] = get_other_letter(genome_file[i]);
    }

    else {
      random_sequence[j++] = genome_file[i];
    }
  }
}

void prefix_trie::build_tree(char* sequence, int seq_len) {
  current = root;
  for(int i = 0; i < seq_len; i++) {

    switch(sequence[i]) {
        case 'A':
        if(!current->nextA) {
          // Allocates memory for new node
          struct Node *new_node = new struct Node();

          // Init new node
          new_node->nextA = NULL;
          new_node->nextC = NULL;
          new_node->nextT = NULL;
          new_node->nextG = NULL;

          // Adds a node to current to new node
          current->nextA = new_node;
          current = new_node;
          num_nodes++;
        }
        else {
          current = current->nextA;
        }
          break;
        case 'C':
          if(!current->nextC) {
            // Allocates memory for new node
            struct Node *new_node = new struct Node();

            // Init new node
            new_node->nextA = NULL;
            new_node->nextC = NULL;
            new_node->nextT = NULL;
            new_node->nextG = NULL;

            // Adds a node to current to new node
            current->nextC = new_node;
            current = new_node;
            num_nodes++;
          }

          else {
            current = current->nextC;
          }

          break;
        case 'T':
        if(!current->nextT) {

          // Allocates memory for new node
          struct Node *new_node = new struct Node();

          // Init new node
          new_node->nextA = NULL;
          new_node->nextC = NULL;
          new_node->nextT = NULL;
          new_node->nextG = NULL;

          // Adds a node to current to new node
          current->nextT = new_node;
          current = new_node;
          num_nodes++;
        }
        else {
          current = current->nextT;
        }
          break;
        case 'G':
        if(!current->nextG) {
          // Allocates memory for new node
          struct Node *new_node = new struct Node();

          // Init new node
          new_node->nextA = NULL;
          new_node->nextC = NULL;
          new_node->nextT = NULL;
          new_node->nextG = NULL;

          // Adds a node to current to new node
          current->nextG = new_node;
          current = new_node;
          num_nodes++;
        }
        else {
          current = current->nextG;
        }
          break;
    }
  }
}

// Adds all paths of trie, and then iterates num_mismatches
void prefix_trie::add_all_paths(struct Node *something) {
  push(something->nextA);
  push(something->nextT);
  push(something->nextG);
  push(something->nextC);
  num_mismatches++;
}

// Pushes a new node onto stack
void prefix_trie::push(struct Node *new_path) {
  branch_stack->next = branch_stack->head;
  branch_stack->head = new_path;
}

// Sets current to next value on stack
void prefix_trie::pop() {
  if(branch_stack->head == NULL) {
    current = NULL;
  }

  else {
    current = branch_stack->head;
    branch_stack->head = branch_stack->next;
  }
}

int prefix_trie::search_tree(char* sequence, int seq_len) {
  best_match = new char[50];
  int index = 0;
  int i = 0;
  current = root;
  while(current != NULL) {
      switch(sequence[i]) {
        case 'A':
          // If no num_mismatches add all new possible locations
          if(current->nextA == NULL && num_mismatches == 0) {
            add_all_paths(current);
            pop();
            best_match[index++] = 'A';
            i++;
          }

          // If 1 num_mismatches, pop a new current off the stack
          else if(current->nextA == NULL && num_mismatches == 1) {
            pop();
          }

          // Set new current and set best_match == node value
          else if(current->nextA != NULL) {
            best_match[index++] = 'A';
            current = current->nextA;
            i++;
          }

          else {
            current = current->nextA;
            i++;
          }
        break;

        case 'C':
          // If no num_mismatches add all new possible locations
          if(current->nextC == NULL && num_mismatches == 0) {
            add_all_paths(current);
            pop();
            best_match[index++] = 'C';
            i++;
          }

          // If 1 num_mismatches, pop a new current off the stack
          else if(current->nextC == NULL && num_mismatches == 1) {
            pop();
          }

          // Set new current and set best_match == node value
          else if(current->nextC != NULL){
            best_match[index++] = 'C';
            current = current->nextC;
            i++;
          }

          else {
            current = current->nextC;
            i++;
          }

        break;

        case 'T':
          // If no num_mismatches add all new possible locations
          if(current->nextT == NULL && num_mismatches == 0) {
            add_all_paths(current);
            pop();
            best_match[index++] = 'T';
            i++;
          }

          // If 1 num_mismatches, pop a new current off the stack
          else if(current->nextT == NULL && num_mismatches == 1) {
            pop();
          }

          // Set new current and set best_match == node value
          else if(current->nextT != NULL){
            best_match[index++] = 'T';
            current = current->nextT;
            i++;
          }

          else {
            current = current->nextT;
            i++;
          }

          break;

        case 'G':
          // If no num_mismatches add all new possible locations
          if(current->nextG == NULL && num_mismatches == 0) {
            add_all_paths(current);
            pop();
            best_match[index++] = 'G';
            i++;
          }

          // If 1 num_mismatches, pop a new current off the stack
          else if(current->nextG == NULL && num_mismatches == 1) {
            pop();
          }

          // Set new current and set best_match == node value
          else if(current->nextG != NULL) {
            best_match[index++] = 'G';
            current = current->nextG;
            i++;
          }

          else {
            current = current->nextG;
            i++;
          }

          break;
        default:
          current = NULL;
          break;
      }
    }

    // If length of best_match string > 35 return a 1 for success
    if(index > 35) {
      return 1;
    }
    else {
      return 0;
    }
}

int main(int argc, char *argv[]) {
  int total_matches = 0;
  prefix_trie *trie;
  trie = new prefix_trie();
  trie->get_length_of_file(argv[3]);
  srand (time(NULL));

  // Runs for Problem-A
  if(strcmp(argv[1], "--A") == 0) {
    for(int i=0; i < atoi(argv[2]); i++) {
      trie->get_random_string(trie->length_of_file);
      trie->build_tree(trie->random_sequence, 36);
    }

    // Gets all matches, then spits out the results
    total_matches = trie->get_all_matches();
    std::cout << "Number of Nodes: " << trie->num_nodes << std::endl;
    std::cout << "Number Matches: " << total_matches << std::endl;
  }

  // Runs for Problem-B
  else if(strcmp(argv[1], "--B") == 0) {
    for(int i=0; i < atoi(argv[2]); i++) {
      trie->get_random_string_error(trie->length_of_file, 0.05);
      trie->build_tree(trie->random_sequence, 36);
      delete trie->random_sequence;
    }

    // Gets all matches, then spits out the results
    total_matches = trie->get_all_matches();
    std::cout << "Number of Nodes: " << trie->num_nodes << std::endl;
    std::cout << "Number Matches: " << total_matches << std::endl;
  }

  delete trie;
}
