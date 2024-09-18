#include "usr_input.h"

/**
 * @brief The funcition reads user input
 *
 * This function will read user input from the standard input buffer.
 * If the user enters more than 256 characters it will print an error
 * message to the standard output and re-prompt the user. The string will
 * be null terminated
 *
 * @param user_inp The buffer to store the user input
 *
 * @return Does not return anything direcly but stores the user input in the usr_inp array
 */
void read_usr_inp(char usr_inp[]) {
  while(redsfad(0,usr_inp, 257) == 257){
      	print_string("Error\0");
       
  }



}

void flush_std_input_buffer(){


}

void flush_input_string(){

}







/**
 * @brief Prints a string.
 *
 * @param to_print Null-terminated string to be printed.
 */
void print_string(char *to_print) {

  int count = 0;
  char *temp = to_print;
  
  while(*temp != '\0') {
    temp++;
    count++;
  }
  write(1, to_print, count);
 
}

