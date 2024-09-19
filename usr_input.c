#include "usr_input.h"
#include <stdio.h>


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
  while(read(FD_STD_INP,usr_inp, MAX_SIZE) >= MAX_SIZE-1){
      	print_string("Error: The input was longer than 256 characters \n \0");
       	flush_std_input_buffer();
	 }
  



}

void flush_std_input_buffer(){
  size_t buff_size = 100;
  char temp_buff[buff_size];
  while((size =read(FD_STD_INP,temp_buff, buff_size)) > 0){
    printf ("T");
    }
   

}


void flush_input_string(char str[]){

}







/**
 * @brief Prints a null terminated string.
 *
 * @param to_print Null-terminated string to be printed.
 */
void print_string(char *to_print) {

  int count = 0;
  char *temp = to_print;
  
  while(*temp != '\0') {
    temp++;
    count++;
        printf ("T");

  }
  
  write(FD_STD_OUT, to_print, count);
 
}

