#include "usr_input.h"
#include <stdio.h>


/**
 * @brief The funcition reads user input
 *
 * This function will read user input from the standard input buffer.
 * If the user enters more than 256 characters, it will print an error
 * message to the standard output and re-prompt the user. The string will
 * be null terminated and wuill be less than 257 characters
 *
 * @param user_inp The buffer to store the user input. The fucntion assumes that the string is 257 bytes
 *
 * @return Does not return anything direcly but stores the user input in the usr_inp array
 */
void read_usr_inp(char usr_inp[]) {
  int count = 0;
  char shell_prompt[] = "jdshell$$: ";
  char error_msg[] ="Error: The input was longer than 256 characters\n";

  print_string(shell_prompt);
  count = read(FD_STD_INP,usr_inp, MAX_SIZE);

  while(count == MAX_SIZE ){
    print_string(error_msg);
    flush_std_input_buffer();
    print_string(shell_prompt);
  
    flush_input_string(usr_inp);
    count = read(FD_STD_INP,usr_inp, MAX_SIZE);
  }

  
  usr_inp[count] = '\0';
 

}


/**
 * @brief Flushes the standard input buffer.
 *
 * This function clears any remaining data in the standard input buffer by
 * reading and discarding up to 1000 characters. It sets the file descriptor
 * for standard input to non-blocking mode first so the read function does
 * not block until the user presses enter. THe original flags are restored
 * afterwards
 *
 * @return This function does not return any value. 
 *
 * @references https://www.linuxtoday.com/blog/blocking-and-non-blocking-i-0/
 *             Used it for learning about fcntl and how to switch a fd to non blockeing
 */
void flush_std_input_buffer(){
  
  int buff_size = 1000;
  char temp_buff[buff_size];
  int previous_flag = fcntl(FD_STD_INP,F_GETFL);

  /*Only turns on the non blocking flag*/
  fcntl(FD_STD_INP,F_SETFL, previous_flag | O_NONBLOCK);
  
  while(read(FD_STD_INP,temp_buff,buff_size) >0);

  fcntl(FD_STD_INP,F_SETFL, previous_flag);
  
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
