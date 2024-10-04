#include "our_string.h"


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
