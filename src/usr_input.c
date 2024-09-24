#include "usr_input.h"
#include <stdio.h>


/**
 * @brief The funcition reads user input
 *
 * This function will read user input from the standard input buffer.
 * If the user enters more than 256 characters, it will print an error
 * message to the standard output and re-prompt the user. The user
 * will also be re-prompted if they enter just a new line. The input string will
 * be null terminated and will be at most 256 characters including the null terminator.
 *
 * @param user_inp The buffer to store the user input. 
 *                 The function assumes that the string has a length of 256 chars.
 *
 * @return Does not return anything direcly but stores the user input in the usr_inp array
 */
void read_usr_inp(char usr_inp[]) {
  ssize_t count = 0;
  char shell_prompt[] = "jdshell$$: ";
  char error_msg[] ="Error: The input was longer than 256 characters\n";
  bool valid_input = FALSE;
  
  while(valid_input == FALSE) {
    
    print_string(shell_prompt);
    count = read(FD_STD_INP, usr_inp, MAX_SIZE);

    /*Exit if read failed*/
    if (count == -1) {
      write(FD_STD_ERR, "Error reading input in read_usr_inp function\n", 46);
      _exit(1); 
    }
    
    
    if(usr_inp[count -1] != '\n') {  /*User entered more than 256 characters*/
      print_string(error_msg);
      flush_std_input_buffer();
    }else if(count >1) {             /*Check if user did not enter an empty line*/
      valid_input = TRUE;
    }
    
  }
  
  usr_inp[count - 1] = '\0';
  
  
}


/**
 * @brief Helper function to read_usr_input for flushing the standard input buffer.
 *
 * This function clears any remaining data in the standard input buffer by
 * reading and discarding characters until a newline is encountered.
 *
 * @return This function does not return any value.
 */
void flush_std_input_buffer(){
  
  size_t  buff_size = 100;
  char temp_buff[buff_size];
  bool input_flushed = FALSE;
  ssize_t count = 0;

  while(input_flushed == FALSE) {  
    count = read(FD_STD_INP, temp_buff, buff_size);

    /*Exit if read failed*/
    if (count == -1) {
      write(FD_STD_ERR, "Error reading input in read_usr_inp function\n", 46);
      _exit(1);
    }

    if(temp_buff[count -1] == '\n') {
      input_flushed = TRUE;
    }
  }
  
}


void flush_input_string(char str[]){

}







/**
 * @brief Prints a null terminated string.
 *
 * @param to_print Null-terminated string to be printed.
 */
void print_string(char *to_print ) {

  int count = 0;
  char *temp = to_print;
  
  while(*temp != '\0') {
    temp++;
    count++;
  }
  
  write(FD_STD_OUT, to_print, count);
 
}


/**
 *  @brief Compares two strings up to a specified number of characters or until the end.
 *
 *
 * Compares str1 and str2 character by character. They must be null termiated.
 * If num_to_compare is bigger than 0, it compares up to that many characters.
 * If num_to_compare is zero or negative, it compares until the end of either string.
 *
 * @param str1 pointer to the first string.
 * @param str2 pointer to the second string.
 * @param num_to_compare Number of characters to compare; if zero or negative, compares
 *                       until the end of either string.
 *
 * @return TRUE if the compared portion of the strings are equal, FALSE otherwise.
 */
bool string_compare(char *str1, char *str2, int num_to_compare){

  bool is_equal = TRUE;
  
  if(num_to_compare > 0) {
    while(num_to_compare > 0 && is_equal) {
      is_equal = (*str1 == *str2);
      str1++;
      str2++;
      num_to_compare--;
    }
    
  }else {
    while( *str1 != '\0' && *str2 != '\0' && is_equal == TRUE) {
      is_equal = (*str1 == *str2);
      str1++;
      str2++;
    }
    is_equal = *str1 == *str2;

  }

  return is_equal;

}
