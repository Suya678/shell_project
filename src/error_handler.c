#include "error_handlers.h"


/**
 * @brief Helper function to read_usr_input for handling errors with read system call
 *
 * If the read system call fails to a interruption by a signal, the shell program
 * can still recover. But if it fails, due to:
 * 
 * 1. The user pressing CTRL D: This means the user wants to exit
 * 2. Any other reason: THe shell should not recover and exit with a failure exit code.
 *
 * @return This function does not return any value.
 */
void handle_read_error(size_t count) {

  print_string("\n");
  if(errno == EINTR) {
    return;
  }
  if(count  == 0) {
    exit(EXIT_SUCCESS); /*User pressed ctrl d to exit*/
  } else {
    perror("ERROR COULD NOT READ IN get_usr_input or flush_std_input_buffer"); /*Something else has gone wrong so exit*/
    exit(EXIT_FAILURE);

  }

}


/**
 * @brief Helper function to for print_string for handling errors with the write system call
 *
 * If the write system call fails due to a interruption by a signal, the process
 * can still recover. But if it fails, due to any other reason, the process will exit.
 * @return This function does not return any value.
 */
void handle_write_error() {
  if(errno == EINTR) {
    return;
  } else {
    perror("Write failed in print string"); /*Something else has gone wrong so exit*/
    exit(EXIT_FAILURE);
  }
  
}


/**
 * @brief Exits the process and prints the error message provided using perror.
 *
 * @param str The error message to be passed to perror for displaying the error.
 *
 * @return This function does not return any value.
 */
void handle_syscall_error(char *str) {
    perror(str);
    exit(EXIT_FAILURE);
}


