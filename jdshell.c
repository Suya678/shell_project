
#include <unistd.h>
#include <fcntl.h>
#include "usr_input.h"
#include <stdio.h>
#include <string.h>
int main(char argc, char *argv[]) {
  char usr_inp[MAX_SIZE];

  read_usr_inp(usr_inp);


  while(string_compare(usr_inp, "exit", 4) != TRUE){
      read_usr_inp(usr_inp);
  }
	
  /*  flush_std_input_buffer();
   */
  return 0;
}
