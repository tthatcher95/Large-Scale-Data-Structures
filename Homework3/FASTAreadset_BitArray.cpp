# include <iostream>
# include <stdlib.h>
# include <unistd.h>
# include <fstream>
# include <cstring>
# include <time.h>
# include <cmath>
# include <bitset>

// Function to convert string to Radix notation
double convert_to_radix(char* sequence) {

  double A = 0;
  double C = 1;
  double G = 2;
  double T = 3;
  int buffer_size = 50;
  double cipher = 0;
  double square = 0;

  int first_half_index = 0;
  int second_half_index = 1;
  int half_of_string = 25;
  int current_power = 2;
  int max_radix_size = 3;

  double* radix;
  char* example = new char[buffer_size];

  example = sequence;
  radix = new double[2];

  // Converts to RADIX notation
  for(int i =0; i < max_radix_size; i++) {
    // Sets the power of current radix alphabet (max of 4 ^ n-1)
    square = pow(4,(current_power));

    // // If i is half, reset the cipher
    // if(i == half_of_string) {
    //   radix[first_half_index] = cipher;
    //   cipher = 0;
    // }

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
  // // Set the second half of the string cipher
  // radix[second_half_index] = cipher;

  return cipher;
}


char *bit_array(char* sequence) {
  int byte = pow(2,29);
  int check_bit = 0;
  double mod_bit;
  double whole_bit;
  double radix;
  double shift;
  char bit_array;
  char* bits;
  radix = convert_to_radix(sequence);

  bits = (char *)&(radix);
  whole_bit = radix / 8.0;
  mod_bit = std::fmod(radix, 8.0);
  shift = 8 - int(mod_bit);

  check_bit = bits[int(mod_bit)];
  std::cout << bits << std::endl;

  check_bit = bits[int(whole_bit)*int(mod_bit) + int(shift)] >> 7;

  std::cout << shift << std::endl;
  std::cout << check_bit << std::endl;

  check_bit = check_bit + pow(2, int(shift - 1));
  std::cout << check_bit << std::endl;

  check_bit = bits[int(mod_bit)] << int(shift);
  check_bit = bits[int(mod_bit) + int(shift)] >> 7;
  std::cout << check_bit << std::endl;

  return bits;
}

int main() {
  char *sequence = "ATA";
  char* bits = bit_array(sequence);

}
