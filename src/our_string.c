#include "our_string.h"

#include "stdio.h"
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
    if(is_equal ==TRUE){   /*making sure both strings have ended*/
      is_equal = (*str1 == *str2);
    }
  }

  return is_equal;

}




/**
 *  @brief Concatinates the source to the destination array
 *
 *
 * Does not do bounds checkign so user has to make sure the destination is big enough to accomodate source
 *
 * @param destination pointer to the string to append to 
 * @param source pointer to the string being appended to destination
 *
 * @return Does not return anything
 */
void my_str_cat(char *source, char *destination){
  while(*destination != '\0')
    destination++;

  while(*source != '\0') {
    *destination = *source;
    destination++; 
    source++;
  }
  
  *destination = '\0';


}




/**
 *  @brief Copies characters from the source string into the destination string until the delimiter or null is encountered
*
 * Does not do bounds checkign so user has to make sure the destination is big enough to accomodate source
 *
 * @param destination pointer to the string being copied to 
 * @param source pointer to the string being copied to destination
 * @param delimiter copying stops when this character is encountered in the source string or null

 * @return Does not return anything
 */
void string_copy(char *source, char *destination, char delimiter) {
  while(*source != delimiter && *source != '\0') {
    *destination = *source;
    destination++;
    source++;
  }

  *destination = '\0';

}
