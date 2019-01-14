#include "suffix_tree.h"

// String with no errors, reads from 0-mersize inside the genome_file
void suffix_tree::get_random_string(int length_file, int mersize) {
  int max_position = rand() % (length_file - mersize);
  random_sequence = new char[50];
  int j=0;
  for(int i=max_position; i < max_position + mersize; i++) {
    random_sequence[j++] = genome_file[i];
  }
}

void suffix_tree::get_length_of_file(char* filename) {
  // Allocates more than enough for the file
  int length_file = 0;

  // Character to be reading in
  char c;
  std::ifstream genome_data(filename);

  // Read in data to an array
  while (genome_data.get(c)) {
    if(c == 'A' || c == 'C' || c == 'T' || c == 'G') {
      genome_file[length_file] = c;
      length_file++;
    }
  }
  genome_data.close();
  length_of_file = length_file;

};

void suffix_tree::split_node(int new_start, char* sequence) {

  // temp node
  suffixNode *temp = new suffixNode();
  temp->nextA = NULL;
  temp->nextC = NULL;
  temp->nextT = NULL;
  temp->nextG = NULL;
  temp->string_start = 0;
  temp->string_end = 0;

  // new node
  suffixNode *new_node = new suffixNode();
  new_node->nextA = NULL;
  new_node->nextC = NULL;
  new_node->nextT = NULL;
  new_node->nextG = NULL;
  new_node->string_start = 0;
  new_node->string_end = 0;

  // Assign variables
  temp->string_start = current->string_start + 1;
  temp->string_end = current->string_end;

  current->string_end = current->string_start + 1;

  // std::cout << "Split Start" << '\n';
  // for(int i = current->string_start; i < current->string_end; i++) {
  //   std::cout << genome_file[i] << '\n';
  // }
  // Switch statement to see where to assign temp
  switch (genome_file[temp->string_start]) {
    case 'A':
      current->nextA = temp;
      nodes++;
      break;
    case 'C':
      current->nextC = temp;
      nodes++;
      break;
    case 'T':
      current->nextT = temp;
      nodes++;
      break;
    case 'G':
      current->nextG = temp;
      nodes++;
      break;
  }

  // Switch to see where to assign new_node
  switch (genome_file[new_start]) {
    case 'A':
      current->nextA = new_node;
      current = current->nextA;
      current->string_start = new_start;
      current->string_end = length_of_file;
      // std::cout << "Start" << '\n';
      //
      // for(int i = current->string_start; i < current->string_end; i++) {
      //   std::cout << genome_file[i] << '\n';
      // }
      nodes++;
      break;
    case 'C':
      current->nextC = new_node;
      current = current->nextC;
      current->string_start = new_start;
      current->string_end = length_of_file;
      // std::cout << "Start" << '\n';
      //
      // for(int i = current->string_start; i < current->string_end; i++) {
      //   std::cout << genome_file[i] << '\n';
      // }
      nodes++;
      break;
    case 'T':
      current->nextT = new_node;
      current = current->nextT;
      current->string_start = new_start;
      current->string_end = length_of_file;
      // std::cout << "Start" << '\n';
      //
      // for(int i = current->string_start; i < current->string_end; i++) {
      //   std::cout << genome_file[i] << '\n';
      // }
      nodes++;
      break;
    case 'G':
      current->nextG = new_node;
      current = current->nextG;
      current->string_start = new_start;
      current->string_end = length_of_file;
      // std::cout << "Start" << '\n';
      //
      // for(int i = current->string_start; i < current->string_end; i++) {
      //   std::cout << genome_file[i] << '\n';
      // }
      nodes++;
      break;
    }
  }

// Function to insert a giant string into a tree
void suffix_tree::insert(char* giant_string) {
  suffixNode *temp = new suffixNode();
  int next_null = 0;
  for(int i = 0; i < length_of_file; i++) {
      current = root;
      next_null = 0;
      suffixNode *new_node = new suffixNode();
      new_node->nextA = NULL;
      new_node->nextC = NULL;
      new_node->nextT = NULL;
      new_node->nextG = NULL;
      new_node->string_start = 0;
      new_node->string_end = 0;

      // Switch statement to handle different node paths
      switch(giant_string[i]) {
        case 'A':
          if(current->nextA == NULL) {
            current->nextA = new_node;
            current = current->nextA;
            current->string_start = i;
            current->string_end = length_of_file;
            // std::cout << "Start" << '\n';
            // for(int i = current->string_start; i < current->string_end; i++) {
            //   std::cout << genome_file[i] << '\n';
            // }
            nodes++;

          }

          else {
            current = current->nextA;
            split_node(i + 1, giant_string);
          }
          break;
        case 'C':
          if(current->nextC == NULL) {
            current->nextC = new_node;
            current = current->nextC;
            current->string_start = i;
            current->string_end = length_of_file;
            // std::cout << "Start" << '\n';
            // for(int i = current->string_start; i < current->string_end; i++) {
            //   std::cout << genome_file[i] << '\n';
            // }
            current = new_node;
            nodes++;
          }

          else {
            current = current->nextC;
            split_node(i + 1, giant_string);
          }
          break;
        case 'T':
          if(current->nextT == NULL) {
            current->nextT = new_node;
            current = current->nextT;
            current->string_start = i;
            current->string_end = length_of_file;
            // std::cout << "Start" << '\n';
            // for(int i = current->string_start; i < current->string_end; i++) {
            //   std::cout << genome_file[i] << '\n';
            // }
            current = new_node;
            nodes++;
          }

          else {
            current = current->nextT;
            split_node(i + 1, giant_string);
          }
          break;

        case 'G':
          if(current->nextG == NULL) {
            current->nextG = new_node;
            current = current->nextG;
            current->string_start = i;
            current->string_end = length_of_file;
            // std::cout << "Start" << '\n';
            // for(int i = current->string_start; i < current->string_end; i++) {
            //   std::cout << genome_file[i] << '\n';
            // }
            current = new_node;
            nodes++;
          }

          else {
            current = current->nextG;
            split_node(i + 1, giant_string);
          }
          break;
      }
    }
  };

// Search function (pretty sure this is where I messed up the logic)
int suffix_tree::search(char* sequence, int len_of_seq) {
  char *s = new char[50];
  int j=0;
  current = root;
  while(current != NULL) {
    // std::cout << current->string_start << '\n';
    // std::cout << current->string_end << '\n';
    // std::cout << j << '\n';
    switch(sequence[j]) {
      case 'A':
          if(current->nextA == NULL) {
            return 0;
          }

          else {
            current = current->nextA;
            for(int i = current->string_start; i < current->string_end; i++) {
              s[j++] = genome_file[i];
              // std::cout << s << '\n';
              if(strcmp(sequence, s) == 0) {
                delete s;
                matches++;
                return 1;
              }
              else if (j >= len_of_seq){
                return 0;
              }
            }
          }

        break;
      case 'C':
        if(current->nextC == NULL) {
          return 0;
        }

        else {
          current = current->nextC;
          for(int i = current->string_start; i < current->string_end; i++) {
            s[j++] = genome_file[i];
            // std::cout << s << '\n';
            if(strcmp(sequence, s) == 0) {
              delete s;
              matches++;

              return 1;
            }
            else if (j >= len_of_seq){
              return 0;
            }
          }
        }
        break;
      case 'T':
        if(current->nextT == NULL) {
          return 0;
        }

        else {
          current = current->nextT;
          for(int i = current->string_start; i < current->string_end; i++) {
            s[j++] = genome_file[i];
            // std::cout << s << '\n';
            if(strcmp(sequence, s) == 0) {
              delete s;
              matches++;

              return 1;
            }
            else if (j >= len_of_seq){
              return 0;
            }
          }
        }
        break;
      case 'G':
        if(current->nextG == NULL) {
          return 0;
        }

        else {
          current = current->nextG;
          for(int i = current->string_start; i < current->string_end; i++) {
            s[j++] = genome_file[i];
            // std::cout << s << '\n';
            if(strcmp(sequence, s) == 0) {
              matches++;
              return 1;
            }
            else if (j >= len_of_seq){
              return 0;
            }
          }
        }
        break;
      default:
        std::cout << "Default" << '\n';
        current = NULL;
        break;
      }
  }

}

int main(int argc, char *argv[]) {
  int a = 0;
  suffix_tree *suffix = new suffix_tree();
  suffix->get_length_of_file(argv[2]);
  suffix->insert(suffix->genome_file);

  if(strcmp(argv[1], "--A") == 0) {
  // 5k random_sequence
  for(int i =0; i < 5000; i++) {
    suffix->get_random_string(suffix->length_of_file, 36);
    a = suffix->search(suffix->random_sequence, 36);
    delete suffix->random_sequence;
  }
  std::cout << "\nNumber of Nodes for 5k: " << suffix->nodes << '\n';
  std::cout << "Number of Matches for 5k: "<< suffix->matches << '\n';

  // 10k random_sequence
  for(int i =0; i < 10000; i++) {
    suffix->get_random_string(suffix->length_of_file, 36);
    a = suffix->search(suffix->random_sequence, 36);
    delete suffix->random_sequence;
  }
  std::cout << "\nNumber of Nodes for 10k: " << suffix->nodes << '\n';
  std::cout << "Number of Matches for 10k: "<< suffix->matches << '\n';

  // 100k random_sequence
  for(int i =0; i < 100000; i++) {
    suffix->get_random_string(suffix->length_of_file, 36);
    a = suffix->search(suffix->random_sequence, 36);
    delete suffix->random_sequence;
  }
  std::cout << "\nNumber of Nodes for 100k: " << suffix->nodes << '\n';
  std::cout << "Number of Matches for 100k: "<< suffix->matches << '\n';
  }
}
