
#include <unistd.h>
#include <fcntl.h>
#include "usr_input.h"

int main(char argc, char *argv[]) {
  char usr_inp[MAX_SIZE];

  read_usr_inp(usr_inp);

  while(string_compare(usr_inp, "exit", 4) != TRUE){
      read_usr_inp(usr_inp);
  }


  return 0;
}
